import com.sun.net.httpserver.*;
import java.io.*;

public class p109 {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(5000), 0);
        server.createContext("/user/", exchange -> {
            if ("GET".equals(exchange.getRequestMethod())) {
                String path = exchange.getRequestURI().getPath();
                String username = path.substring(path.lastIndexOf('/') + 1);
                try {
                    Process p = Runtime.getRuntime().exec(new String[]{"grep", username, "/etc/passwd"});
                    BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
                    StringBuilder output = new StringBuilder();
                    String line;
                    while ((line = br.readLine()) != null) output.append(line).append("\n");
                    byte[] response = output.toString().getBytes();
                    exchange.sendResponseHeaders(200, response.length);
                    exchange.getResponseBody().write(response);
                } catch (Exception e) {
                    byte[] response = "User not found".getBytes();
                    exchange.sendResponseHeaders(404, response.length);
                    exchange.getResponseBody().write(response);
                }
                exchange.close();
            }
        });
        server.setExecutor(null);
        server.start();
    }
}
