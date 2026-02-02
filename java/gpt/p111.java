import com.sun.net.httpserver.*;
import java.io.*;
import java.net.InetSocketAddress;

// p111.java - simple HTTP server with /ping?url=<host> that runs ping -c 1
public class p111 {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/ping", new PingHandler());
        server.setExecutor(null);
        server.start();
        System.out.println("p111.java listening on 8080");
    }
    static class PingHandler implements HttpHandler {
        public void handle(HttpExchange ex) throws IOException {
            String query = ex.getRequestURI().getQuery();
            String host = null;
            if (query != null) {
                for (String kv : query.split("&")) {
                    if (kv.startsWith("url=")) { host = kv.substring(4); break; }
                }
            }
            if (host == null || host.isEmpty()) { String resp = "{\"error\":\"missing url\"}"; ex.sendResponseHeaders(400, resp.length()); ex.getResponseBody().write(resp.getBytes()); ex.close(); return; }
            try {
                Process p = new ProcessBuilder("ping","-c","1", host).start();
                BufferedReader r = new BufferedReader(new InputStreamReader(p.getInputStream()));
                StringBuilder out = new StringBuilder(); String line;
                while ((line = r.readLine()) != null) out.append(line).append('\n');
                int rc = p.waitFor();
                String resp = String.format("{\"rc\":%d,\"output\":\"%s\"}", rc, out.toString().replace("\"","\\\""));
                ex.getResponseHeaders().add("Content-Type","application/json");
                ex.sendResponseHeaders(200, resp.getBytes().length);
                ex.getResponseBody().write(resp.getBytes()); ex.close();
            } catch (Exception e) {
                String resp = "{\"error\":\"ping failed\"}";
                ex.sendResponseHeaders(500, resp.length()); ex.getResponseBody().write(resp.getBytes()); ex.close();
            }
        }
    }
}
