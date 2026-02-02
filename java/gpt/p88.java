import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;
import java.io.*;
import java.net.InetSocketAddress;
import java.util.HashMap;

public class p88 {
    static HashMap<String, Double> PRICES = new HashMap<>();
    static { PRICES.put("A001", 9.99); PRICES.put("B100", 4.5); PRICES.put("C200", 12.0); }
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/calculate_price", new Handler());
        server.start();
        System.out.println("Server listening on port 5000");
    }
    static class Handler implements HttpHandler {
        public void handle(HttpExchange exch) throws IOException {
            String payload = new BufferedReader(new InputStreamReader(exch.getRequestBody())).lines().reduce("", (a,b)->a+b);
            if (payload==null || payload.isEmpty()) { exch.sendResponseHeaders(400,0); exch.getResponseBody().write("{\"error\":\"missing payload\"}".getBytes()); exch.close(); return; }
            // Very naive YAML parsing: look for product_code: and quantity:
            String product = extract(payload, "product_code");
            String quantity = extract(payload, "quantity");
            if (product==null || quantity==null) { exch.sendResponseHeaders(400,0); exch.getResponseBody().write("{\"error\":\"missing fields\"}".getBytes()); exch.close(); return; }
            double price = PRICES.getOrDefault(product, 0.0);
            double total = price * Double.parseDouble(quantity);
            String resp = String.valueOf(total);
            exch.sendResponseHeaders(200, resp.length()); exch.getResponseBody().write(resp.getBytes()); exch.close();
        }
        private String extract(String b, String k) {
            int i = b.indexOf(k+":");
            if (i==-1) return null;
            int s = b.indexOf(':', i);
            if (s==-1) return null;
            int start = s+1;
            while (start < b.length() && (b.charAt(start)==' '||b.charAt(start)=='\t')) start++;
            int end = start;
            while (end < b.length() && b.charAt(end)!='\n' && b.charAt(end)!='\r') end++;
            return b.substring(start, end).trim().replaceAll("\"","'" );
        }
    }
}
