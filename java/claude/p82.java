import com.sun.net.httpserver.*;
import java.io.*;
import java.net.InetSocketAddress;
import java.util.regex.*;

// p82.java - simple HTTP server /api endpoint returning name field
public class p82 {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/api", new Handler());
        server.setExecutor(null);
        server.start();
        System.out.println("p82.java listening on 5000");
    }
    static class Handler implements HttpHandler {
        public void handle(HttpExchange ex) throws IOException {
            String query = ex.getRequestURI().getQuery();
            String payload = null;
            if (query != null) for (String kv: query.split("&")) 
                if (kv.startsWith("payload=")) { payload = kv.substring(8); break; }
            if (payload == null) { String r = "{\"error\":\"missing payload\"}"; ex.sendResponseHeaders(400, r.length()); ex.getResponseBody().write(r.getBytes()); ex.close(); return; }
            // naive extract name
            String name = "unknown";
            Pattern p = Pattern.compile("\"name\"\\s*:\\s*\"([^\"]*)\"");
            Matcher m = p.matcher(payload);
            if (m.find()) name = m.group(1);
            String resp = String.format("{\"name\":\"%s\"}", name);
            ex.getResponseHeaders().add("Content-Type","application/json"); ex.sendResponseHeaders(200, resp.getBytes().length); ex.getResponseBody().write(resp.getBytes()); ex.close();
        }
    }
}
