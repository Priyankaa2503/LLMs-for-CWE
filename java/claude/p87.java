import com.sun.net.httpserver.*;
import java.io.*;

public class p87 {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(8080), 0);
        server.createContext("/api", exchange -> {
            if ("POST".equals(exchange.getRequestMethod())) {
                BufferedReader br = new BufferedReader(new InputStreamReader(exchange.getRequestBody()));
                StringBuilder sb = new StringBuilder(); String line;
                while ((line = br.readLine()) != null) sb.append(line);
                String json = sb.toString();
                if (json.contains("location") && json.contains("date")) {
                    byte[] response = "{\"temperature\":68.0,\"unit\":\"F\"}".getBytes();
                    exchange.sendResponseHeaders(200, response.length);
                    exchange.getResponseBody().write(response);
                } else {
                    byte[] response = "{\"error\":\"missing required fields\"}".getBytes();
                    exchange.sendResponseHeaders(400, response.length);
                    exchange.getResponseBody().write(response);
                }
                exchange.close();
            }
        });
        server.setExecutor(null);
        server.start();
    }
}
