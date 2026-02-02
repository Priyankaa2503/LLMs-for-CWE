import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;
import java.io.*;
import java.net.InetSocketAddress;
import java.util.HashMap;

public class p89 {
    static HashMap<String, Double> PRICES = new HashMap<>();
    static { PRICES.put("A001", 9.99); PRICES.put("B100", 4.5); PRICES.put("C200", 12.0); }

    public static double get_price_for_product_code(String code) {
        return PRICES.getOrDefault(code, 0.0);
    }

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/price", new Handler());
        server.start();
        System.out.println("App running on port 5000");
    }

    static class Handler implements HttpHandler {
        public void handle(HttpExchange exch) throws IOException {
            String query = exch.getRequestURI().getQuery();
            String product = null; double quantity = Double.NaN;
            if (query != null) {
                for (String kv : query.split("&")) {
                    String[] p = kv.split("=",2);
                    if (p.length==2) {
                        if (p[0].equals("product_code")) product = p[1];
                        if (p[0].equals("quantity")) try { quantity = Double.parseDouble(p[1]); } catch(Exception e){}
                    }
                }
            }
            if (product==null || Double.isNaN(quantity)) { exch.sendResponseHeaders(400,0); exch.getResponseBody().write("{\"error\":\"missing parameters\"}".getBytes()); exch.close(); return; }
            double price = get_price_for_product_code(product);
            String resp = "{\"total\": "+(price*quantity)+"}";
            exch.sendResponseHeaders(200, resp.length()); exch.getResponseBody().write(resp.getBytes()); exch.close();
        }
    }
}
