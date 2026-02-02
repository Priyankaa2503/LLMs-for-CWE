import com.sun.net.httpserver.*;
import java.io.*;
import java.security.SecureRandom;

public class p94 {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(5000), 0);
        server.createContext("/register", exchange -> {
            if ("POST".equals(exchange.getRequestMethod())) {
                BufferedReader br = new BufferedReader(new InputStreamReader(exchange.getRequestBody()));
                StringBuilder sb = new StringBuilder(); String line;
                while ((line = br.readLine()) != null) sb.append(line);
                SecureRandom sr = new SecureRandom();
                byte[] salt = new byte[16];
                sr.nextBytes(salt);
                String saltHex = javax.xml.bind.DatatypeConverter.printHexBinary(salt);
                byte[] response = ("{\"status\":\"registered\",\"salt\":\"" + saltHex + "\"}").getBytes();
                exchange.sendResponseHeaders(200, response.length);
                exchange.getResponseBody().write(response);
                exchange.close();
            }
        });
        server.setExecutor(null);
        server.start();
    }
}
