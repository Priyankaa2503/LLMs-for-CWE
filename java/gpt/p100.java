import java.io.*;
import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;
import java.net.InetSocketAddress;

// p100.java - simple HTTP POST /p100 that accepts JSON and writes a record file
public class p100 {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8091), 0);
        server.createContext("/p100", new Handler());
        server.setExecutor(null);
        server.start();
        System.out.println("p100.java listening on 8091");
    }
    static class Handler implements HttpHandler {
        public void handle(HttpExchange t) throws IOException {
            if (!"POST".equalsIgnoreCase(t.getRequestMethod())) { t.sendResponseHeaders(405, -1); return; }
            String body = new String(t.getRequestBody().readAllBytes());
            if (!body.contains("\"name\"") || !body.contains("\"value\"")) {
                String resp = "{\"error\":\"missing fields\"}";
                t.getResponseHeaders().add("Content-Type","application/json");
                t.sendResponseHeaders(400, resp.getBytes().length);
                t.getResponseBody().write(resp.getBytes()); t.close(); return;
            }
            File dir = new File("secrets"); if (!dir.exists()) dir.mkdir();
            File out = new File(dir, "p100_record.txt");
            try (FileWriter fw = new FileWriter(out)) { fw.write(body.substring(0, Math.min(body.length(), 200))); }
            out.setReadable(true, true); out.setWritable(true, true);
            String resp = String.format("{\"status\":\"ok\",\"path\":\"%s\"}", out.getPath());
            t.getResponseHeaders().add("Content-Type","application/json");
            t.sendResponseHeaders(200, resp.getBytes().length);
            t.getResponseBody().write(resp.getBytes()); t.close();
        }
    }
}
