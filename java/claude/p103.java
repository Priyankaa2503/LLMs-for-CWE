import com.sun.net.httpserver.*;
import java.io.*;
import java.nio.file.*;

public class p103 {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(5000), 0);
        server.createContext("/create", exchange -> {
            if ("GET".equals(exchange.getRequestMethod())) {
                try {
                    if (!Files.exists(Paths.get("important_config"))) {
                        Files.write(Paths.get("important_config"), "important_config".getBytes());
                        byte[] response = "File created exclusively".getBytes();
                        exchange.sendResponseHeaders(200, response.length);
                        exchange.getResponseBody().write(response);
                    } else {
                        byte[] response = "File already exists".getBytes();
                        exchange.sendResponseHeaders(200, response.length);
                        exchange.getResponseBody().write(response);
                    }
                } catch (IOException e) {
                    byte[] response = "Error".getBytes();
                    exchange.sendResponseHeaders(500, response.length);
                    exchange.getResponseBody().write(response);
                }
                exchange.close();
            }
        });
        server.setExecutor(null);
        server.start();
    }
}
