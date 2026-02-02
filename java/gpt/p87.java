import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;
import java.io.*;
import java.net.InetSocketAddress;
import java.sql.*;

public class p87 {
    public static void main(String[] args) throws Exception {
        try (Connection conn = DriverManager.getConnection("jdbc:sqlite:sensor.db")) {
            conn.createStatement().execute("CREATE TABLE IF NOT EXISTS Sensor(latitude TEXT, longitude TEXT, date TEXT, temperature REAL)");
        } catch (Exception e) {}
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/api/temperature_for_location", new Handler());
        server.start();
        System.out.println("Server listening on port 5000");
    }
    static class Handler implements HttpHandler {
        public void handle(HttpExchange exch) throws IOException {
            if (!"POST".equalsIgnoreCase(exch.getRequestMethod())) { exch.sendResponseHeaders(405, -1); return; }
            String body = new BufferedReader(new InputStreamReader(exch.getRequestBody())).lines().reduce("", (a,b)->a+b);
            String lat = extract(body, "latitude");
            String lon = extract(body, "longitude");
            String date = extract(body, "date");
            if (lat==null||lon==null||date==null) { sendJson(exch,400,"{\"error\":\"missing parameters\"}"); return; }
            Double val = queryTemp(lat, lon, date);
            if (val==null) { sendJson(exch,404,"{\"error\":\"not found\"}"); return; }
            sendJson(exch,200,"{\"temperature\":"+val+"}");
        }
        private void sendJson(HttpExchange exch,int code,String body) throws IOException { exch.getResponseHeaders().add("Content-Type","application/json"); exch.sendResponseHeaders(code, body.length()); exch.getResponseBody().write(body.getBytes()); exch.close(); }
        private String extract(String b,String k){ int i=b.indexOf('"'+k+'"'); if (i==-1) return null; int c=b.indexOf(':',i); if (c==-1) return null; int s=b.indexOf('"',c); if (s==-1) return null; int e=b.indexOf('"',s+1); if (e==-1) return null; return b.substring(s+1,e); }
        private Double queryTemp(String lat,String lon,String date){ try (Connection conn=DriverManager.getConnection("jdbc:sqlite:sensor.db")){
            PreparedStatement ps=conn.prepareStatement("SELECT temperature FROM Sensor WHERE latitude=? AND longitude=? AND date=? LIMIT 1");
            ps.setString(1,lat); ps.setString(2,lon); ps.setString(3,date);
            ResultSet rs=ps.executeQuery(); if (rs.next()) return rs.getDouble(1); } catch(Exception e){} return null; }
    }
}
