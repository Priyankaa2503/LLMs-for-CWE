import com.sun.net.httpserver.*;
import java.io.*;
import java.util.regex.*;

public class p83 {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(8080), 0);
        server.createContext("/api", exchange -> {
            if ("POST".equals(exchange.getRequestMethod())) {
                BufferedReader br = new BufferedReader(new InputStreamReader(exchange.getRequestBody()));
                StringBuilder sb = new StringBuilder(); String line;
                while ((line = br.readLine()) != null) sb.append(line);
                String json = sb.toString();
                Pattern p = Pattern.compile("\"name\"\\s*:\\s*\"([^\"]+)\"");
                Matcher m = p.matcher(json);
                if (m.find()) {
                    String name = m.group(1);
                    byte[] response = ("{\"name\":\"" + name + "\"}").getBytes();
                    exchange.sendResponseHeaders(200, response.length);
                    exchange.getResponseBody().write(response);
                } else {
                    byte[] response = "{\"error\":\"missing name\"}".getBytes();
                    exchange.sendResponseHeaders(400, response.length);
                    exchange.getResponseBody().write(response);
                }
                exchange.close();
            }
        });
        server.setExecutor(null);
        server.start();
        System.out.println("Server on port 8080");
    }
}
