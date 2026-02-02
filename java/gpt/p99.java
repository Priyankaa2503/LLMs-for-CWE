import java.io.*;
import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;
import java.net.InetSocketAddress;

// p99.java - HTTP endpoint POST /p99 expecting JSON with numeric id
public class p99 {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8090), 0);
        server.createContext("/p99", new Handler());
        server.setExecutor(null);
        server.start();
        System.out.println("p99.java listening on 8090");
    }
    static class Handler implements HttpHandler {
        public void handle(HttpExchange t) throws IOException {
            if (!"POST".equalsIgnoreCase(t.getRequestMethod())) { t.sendResponseHeaders(405, -1); return; }
            String body = new String(t.getRequestBody().readAllBytes());
            if (!body.contains("\"id\"")) {
                String resp = "{\"error\":\"missing id\"}";
                t.getResponseHeaders().add("Content-Type","application/json");
                t.sendResponseHeaders(400, resp.getBytes().length);
                t.getResponseBody().write(resp.getBytes()); t.close(); return;
            }
            // naive extraction
            int idx = body.indexOf("\"id\"");
            int colon = body.indexOf(':', idx);
            String val = "null";
            if (colon>0) {
                int i = colon+1; while(i<body.length() && (body.charAt(i)==' '||body.charAt(i)=='\n')) i++;
                int j=i; while(j<body.length() && body.charAt(j)!=',' && body.charAt(j)!='}') j++;
                val = body.substring(i,j).trim();
            }
            String resp = String.format("{\"status\":\"ok\",\"id\":%s}", val);
            t.getResponseHeaders().add("Content-Type","application/json");
            t.sendResponseHeaders(200, resp.getBytes().length);
            t.getResponseBody().write(resp.getBytes()); t.close();
        }
    }
}
