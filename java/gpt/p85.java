import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;
import java.io.*;
import java.net.InetSocketAddress;
import java.sql.*;

public class p85 {
    public static void main(String[] args) throws Exception {
        // create sqlite DB if not exists
        Class.forName("org.sqlite.JDBC");
        try (Connection conn = DriverManager.getConnection("jdbc:sqlite:sensor.db")) {
            conn.createStatement().execute("CREATE TABLE IF NOT EXISTS Sensor(latitude TEXT, longitude TEXT, date TEXT, temperature REAL)");
        } catch (Exception e) {
            // ignore setup errors
        }

        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/api/temperature_for_location", new Handler());
        server.start();
        System.out.println("Server listening on port 5000");
    }

    static class Handler implements HttpHandler {
        public void handle(HttpExchange exch) throws IOException {
            if (!"POST".equalsIgnoreCase(exch.getRequestMethod())) { exch.sendResponseHeaders(405, -1); return; }
            String body = new BufferedReader(new InputStreamReader(exch.getRequestBody())).lines().reduce("", (a,b)->a+b);
            // naive JSON parse for fields
            String lat = extract(body, "latitude");
            String lon = extract(body, "longitude");
            String date = extract(body, "date");
            if (lat==null || lon==null || date==null) {
                exch.sendResponseHeaders(400, 0); exch.getResponseBody().write("{\"error\":\"missing parameters\"}".getBytes()); exch.close(); return;
            }
            Double temp = queryTemp(lat, lon, date);
            if (temp==null) { exch.sendResponseHeaders(404,0); exch.getResponseBody().write("{\"error\":\"not found\"}".getBytes()); exch.close(); return; }
            String resp = "{\"temperature\": "+temp+"}";
            exch.sendResponseHeaders(200, resp.length()); exch.getResponseBody().write(resp.getBytes()); exch.close();
        }
        private String extract(String body, String key) {
            int k = body.indexOf('"'+key+'"');
            if (k==-1) return null;
            int c = body.indexOf(':', k);
            if (c==-1) return null;
            int s = body.indexOf('"', c);
            if (s==-1) return null;
            int e = body.indexOf('"', s+1);
            if (e==-1) return null;
            return body.substring(s+1,e);
        }
        private Double queryTemp(String lat, String lon, String date) {
            try (Connection conn = DriverManager.getConnection("jdbc:sqlite:sensor.db")) {
                PreparedStatement ps = conn.prepareStatement("SELECT temperature FROM Sensor WHERE latitude=? AND longitude=? AND date=? LIMIT 1");
                ps.setString(1, lat); ps.setString(2, lon); ps.setString(3, date);
                ResultSet rs = ps.executeQuery();
                if (rs.next()) return rs.getDouble(1);
            } catch (Exception e) { }
            return null;
        }
    }
}
