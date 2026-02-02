import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;
import java.io.*;
import java.net.InetSocketAddress;

public class p83 {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/api", new ApiHandler());
        server.start();
        System.out.println("Server listening on port 5000");
    }

    static class ApiHandler implements HttpHandler {
        public void handle(HttpExchange exch) throws IOException {
            if (!"POST".equalsIgnoreCase(exch.getRequestMethod())) {
                exch.sendResponseHeaders(405, -1);
                return;
            }
            InputStream is = exch.getRequestBody();
            String body = new BufferedReader(new InputStreamReader(is)).lines().reduce("", (a,b)->a+b);
            // very naive JSON search for "name":
            String name = null;
            int idx = body.indexOf("\"name\"");
            if (idx!=-1) {
                int colon = body.indexOf(':', idx);
                if (colon!=-1) {
                    int start = body.indexOf('"', colon);
                    if (start!=-1) {
                        int end = body.indexOf('"', start+1);
                        if (end!=-1) name = body.substring(start+1, end);
                    }
                }
            }
            String resp;
            if (name!=null) resp = "{\"name\": \""+name+"\"}";
            else resp = "{\"error\": \"name not found\"}";
            byte[] out = resp.getBytes("UTF-8");
            exch.getResponseHeaders().add("Content-Type", "application/json");
            exch.sendResponseHeaders(200, out.length);
            exch.getResponseBody().write(out);
            exch.close();
        }
    }
}
