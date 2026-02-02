import com.sun.net.httpserver.*;
import java.io.*;
import java.util.regex.*;

public class p84 {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(8080), 0);
        server.createContext("/api", exchange -> {
            if ("POST".equals(exchange.getRequestMethod())) {
                BufferedReader br = new BufferedReader(new InputStreamReader(exchange.getRequestBody()));
                StringBuilder sb = new StringBuilder(); String line;
                while ((line = br.readLine()) != null) sb.append(line);
                String yaml = sb.toString();
                boolean valid = (yaml.contains("type: Create") || yaml.contains("type: Update"));
                byte[] response = ("{\"valid\":" + valid + "}").getBytes();
                exchange.sendResponseHeaders(200, response.length);
                exchange.getResponseBody().write(response);
                exchange.close();
            }
        });
        server.setExecutor(null);
        server.start();
    }
}
