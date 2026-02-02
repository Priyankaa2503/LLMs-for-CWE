import com.sun.net.httpserver.*;
import java.io.*;
import java.nio.file.*;
import java.nio.file.attribute.*;

public class p107 {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(5000), 0);
        server.createContext("/create", exchange -> {
            if ("GET".equals(exchange.getRequestMethod())) {
                try {
                    Files.write(Paths.get("secret.txt"), "U2FsdGVkX1/R+WzJcxgvX/Iw==".getBytes());
                    PosixFilePermissions.fromString("--w-------");
                    byte[] response = "Permissions: 0o200".getBytes();
                    exchange.sendResponseHeaders(200, response.length);
                    exchange.getResponseBody().write(response);
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
