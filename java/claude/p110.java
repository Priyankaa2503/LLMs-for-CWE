import com.sun.net.httpserver.*;
import java.io.*;

public class p110 {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(5000), 0);
        server.createContext("/user/", exchange -> {
            if ("GET".equals(exchange.getRequestMethod())) {
                String path = exchange.getRequestURI().getPath();
                String username = path.substring(path.lastIndexOf('/') + 1);
                try {
                    Process p = Runtime.getRuntime().exec(new String[]{"id", username});
                    int exitCode = p.waitFor();
                    byte[] response = ("Exit status: " + exitCode).getBytes();
                    exchange.sendResponseHeaders(200, response.length);
                    exchange.getResponseBody().write(response);
                } catch (Exception e) {
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
