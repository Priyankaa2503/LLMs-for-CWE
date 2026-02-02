import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;
import java.io.*;
import java.net.InetSocketAddress;

// p98.java - simple HTTP server that accepts JSON POST and returns keys
public class p98 {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8088), 0);
        server.createContext("/p98", new Handler());
        server.setExecutor(null);
        server.start();
        System.out.println("p98.java listening on 8088");
    }
    static class Handler implements HttpHandler {
        public void handle(HttpExchange t) throws IOException {
            if (!"POST".equalsIgnoreCase(t.getRequestMethod())) {
                t.sendResponseHeaders(405, -1);
                return;
            }
            InputStream is = t.getRequestBody();
            String body = new String(is.readAllBytes());
            String response;
            if (!body.trim().startsWith("{")) {
                response = "{\"error\":\"invalid json\"}";
                t.getResponseHeaders().add("Content-Type", "application/json");
                t.sendResponseHeaders(400, response.getBytes().length);
                t.getResponseBody().write(response.getBytes());
                t.close();
                return;
            }
            // naive counting of '"' pairs for approximate key count
            int quotes=0; for(char c: body.toCharArray()) if(c=='\"') quotes++;
            int keys = quotes/2;
            response = String.format("{\"status\":\"ok\",\"approx_keys\":%d}", keys);
            t.getResponseHeaders().add("Content-Type", "application/json");
            t.sendResponseHeaders(200, response.getBytes().length);
            t.getResponseBody().write(response.getBytes());
            t.close();
        }
    }
}
