import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;
import java.io.*;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class p90 {
    static Map<String, Double> PRICES = new HashMap<>();
    static { PRICES.put("A001",9.99); PRICES.put("B100",4.5); PRICES.put("C200",12.0); }
    public static double getPrice(String code) { return PRICES.getOrDefault(code, 0.0); }
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000),0);
        server.createContext("/calculate_price", new Handler());
        server.start();
        System.out.println("Server listening on port 5000");
    }
    static class Handler implements HttpHandler {
        public void handle(HttpExchange exch) throws IOException {
            String body = new BufferedReader(new InputStreamReader(exch.getRequestBody())).lines().reduce("", (a,b)->a+b);
            // naive YAML parsing: look for product_code: and quantity:
            String product = extractYamlValue(body, "product_code");
            String quantity = extractYamlValue(body, "quantity");
            if (product==null || quantity==null) { exch.sendResponseHeaders(400,0); exch.getResponseBody().close(); return; }
            double total = getPrice(product) * Double.parseDouble(quantity);
            String resp = "total: " + total + "\n";
            exch.getResponseHeaders().add("Content-Type","text/yaml");
            exch.sendResponseHeaders(200, resp.length());
            exch.getResponseBody().write(resp.getBytes());
            exch.close();
        }
        private String extractYamlValue(String body, String key) {
            int i = body.indexOf(key+":"); if (i==-1) return null;
            int s = body.indexOf(':', i)+1; while (s<body.length() && Character.isWhitespace(body.charAt(s))) s++;
            int e = s; while (e<body.length() && body.charAt(e)!='\n' && body.charAt(e)!='\r') e++;
            return body.substring(s,e).trim();
        }
    }
}
