import com.sun.net.httpserver.*;
import java.io.*;

public class p113 {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(5000), 0);
        server.createContext("/ping/", exchange -> {
            if ("GET".equals(exchange.getRequestMethod())) {
                String path = exchange.getRequestURI().getPath();
                String url = path.substring(path.lastIndexOf('/') + 1);
                try {
                    Process p = Runtime.getRuntime().exec(new String[]{"ping", "-c", "1", url});
                    int exitCode = p.waitFor();
                    String result = (exitCode == 0) ? "URL " + url + " is alive" : "URL " + url + " is not alive";
                    byte[] response = result.getBytes();
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
