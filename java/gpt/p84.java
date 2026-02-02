import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;
import java.io.*;
import java.net.InetSocketAddress;

// Note: this implementation does a naive check for 'type' and 'name' inside the body
public class p84 {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/", new Handler());
        server.start();
        System.out.println("Server listening on port 5000");
    }

    static class Handler implements HttpHandler {
        public void handle(HttpExchange exch) throws IOException {
            InputStream is = exch.getRequestBody();
            String body = new BufferedReader(new InputStreamReader(is)).lines().reduce("", (a,b)->a+b);
            if (body == null || body.isEmpty()) {
                exch.sendResponseHeaders(400, 0);
                exch.getResponseBody().write("{\"error\":\"missing payload parameter\"}".getBytes());
                exch.close();
                return;
            }
            // naive checks (not real YAML parsing)
            if (body.contains("type: Create") || body.contains("type: 'Create'") || body.contains("type: \"Create\"")) {
                String resp = "{\"error\":\"create not allowed\"}";
                exch.sendResponseHeaders(400, resp.length());
                exch.getResponseBody().write(resp.getBytes());
                exch.close();
                return;
            }
            if (body.contains("type: Update") && body.contains("name: UnsafeDeserialization")) {
                String resp = "{\"error\":\"unsafe deserialization detected\"}";
                exch.sendResponseHeaders(400, resp.length());
                exch.getResponseBody().write(resp.getBytes());
                exch.close();
                return;
            }
            String ok = "{\"status\":\"ok\"}";
            exch.sendResponseHeaders(200, ok.length());
            exch.getResponseBody().write(ok.getBytes());
            exch.close();
        }
    }
}
