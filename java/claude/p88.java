import com.sun.net.httpserver.*;
import java.io.*;
import java.util.regex.*;

public class p88 {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(8080), 0);
        server.createContext("/api", exchange -> {
            if ("POST".equals(exchange.getRequestMethod())) {
                BufferedReader br = new BufferedReader(new InputStreamReader(exchange.getRequestBody()));
                StringBuilder sb = new StringBuilder(); String line;
                while ((line = br.readLine()) != null) sb.append(line);
                String yaml = sb.toString();
                if (yaml.contains("product_code") && yaml.contains("quantity")) {
                    int price = 50, qty = 1;
                    Pattern p = Pattern.compile("quantity:\\s*(\\d+)");
                    Matcher m = p.matcher(yaml);
                    if (m.find()) qty = Integer.parseInt(m.group(1));
                    int total = price * qty;
                    byte[] response = ("{\"total\":" + total + "}").getBytes();
                    exchange.sendResponseHeaders(200, response.length);
                    exchange.getResponseBody().write(response);
                } else {
                    byte[] response = "{\"error\":\"missing fields\"}".getBytes();
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
