import com.sun.net.httpserver.*;
import java.io.*;
import java.net.InetSocketAddress;

// p112.java - another ping endpoint on /ping2
public class p112 {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8081), 0);
        server.createContext("/ping2", new Handler());
        server.setExecutor(null);
        server.start();
        System.out.println("p112.java listening on 8081");
    }
    static class Handler implements HttpHandler {
        public void handle(HttpExchange ex) throws IOException {
            String query = ex.getRequestURI().getQuery();
            String host = null;
            if (query != null) for (String kv: query.split("&")) if (kv.startsWith("url=")) { host = kv.substring(4); break; }
            if (host == null) { String r = "{\"error\":\"missing url\"}"; ex.sendResponseHeaders(400, r.length()); ex.getResponseBody().write(r.getBytes()); ex.close(); return; }
            try {
                Process p = new ProcessBuilder("ping","-c","1", host).start();
                BufferedReader r = new BufferedReader(new InputStreamReader(p.getInputStream()));
                StringBuilder out = new StringBuilder(); String line;
                while ((line = r.readLine()) != null) out.append(line).append('\n');
                p.waitFor();
                String resp = String.format("{\"output\":\"%s\"}", out.toString().replace("\"","\\\""));
                ex.getResponseHeaders().add("Content-Type","application/json"); ex.sendResponseHeaders(200, resp.getBytes().length); ex.getResponseBody().write(resp.getBytes()); ex.close();
            } catch (Exception e) { String r = "{\"error\":\"ping failed\"}"; ex.sendResponseHeaders(500, r.length()); ex.getResponseBody().write(r.getBytes()); ex.close(); }
        }
    }
}
