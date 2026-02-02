import com.sun.net.httpserver.*;
import java.io.*;
import java.util.regex.*;

public class p85 {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(8080), 0);
        server.createContext("/api", exchange -> {
            if ("POST".equals(exchange.getRequestMethod())) {
                BufferedReader br = new BufferedReader(new InputStreamReader(exchange.getRequestBody()));
                StringBuilder sb = new StringBuilder(); String line;
                while ((line = br.readLine()) != null) sb.append(line);
                String json = sb.toString();
                boolean hasLat = json.contains("latitude");
                boolean hasLon = json.contains("longitude");
                boolean hasDate = json.contains("date");
                if (hasLat && hasLon && hasDate) {
                    byte[] response = "{\"temperature\":72.5,\"unit\":\"F\"}".getBytes();
                    exchange.sendResponseHeaders(200, response.length);
                    exchange.getResponseBody().write(response);
                } else {
                    byte[] response = "{\"error\":\"missing parameters\"}".getBytes();
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
