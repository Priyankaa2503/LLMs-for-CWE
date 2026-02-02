import com.sun.net.httpserver.*;
import java.io.*;

public class p114 {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(5000), 0);
        server.createContext("/ls", exchange -> {
            if ("GET".equals(exchange.getRequestMethod())) {
                String dir = exchange.getRequestURI().getQuery() != null ? 
                    exchange.getRequestURI().getQuery().replaceAll("dir=", "") : ".";
                try {
                    Process p = Runtime.getRuntime().exec(new String[]{"ls", "-la", dir});
                    BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
                    StringBuilder output = new StringBuilder();
                    String line;
                    while ((line = br.readLine()) != null) output.append(line).append("\n");
                    byte[] response = output.toString().getBytes();
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
