import com.sun.net.httpserver.*;
import java.io.*;
import java.security.MessageDigest;

public class p90 {
    static int getPriceForProductCode(String code) {
        switch(code) {
            case "PROD001": return 100;
            case "PROD002": return 200;
            default: return 50;
        }
    }
    
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(5000), 0);
        server.createContext("/register", exchange -> {
            if ("POST".equals(exchange.getRequestMethod())) {
                BufferedReader br = new BufferedReader(new InputStreamReader(exchange.getRequestBody()));
                StringBuilder sb = new StringBuilder(); String line;
                while ((line = br.readLine()) != null) sb.append(line);
                String data = sb.toString();
                if (data.contains("username") && data.contains("password")) {
                    byte[] response = "{\"status\":\"registered\"}".getBytes();
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
