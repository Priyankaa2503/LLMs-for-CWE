import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;
import java.io.*;
import java.net.InetSocketAddress;
import java.sql.*;

public class p86 {
    public static void main(String[] args) throws Exception {
        try (Connection conn = DriverManager.getConnection("jdbc:sqlite:sensor.db")) {
            conn.createStatement().execute("CREATE TABLE IF NOT EXISTS Sensor(latitude TEXT, longitude TEXT, year TEXT, month TEXT, day TEXT, grib_file TEXT, temperature REAL)");
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
            String year = extract(body, "year");
            String month = extract(body, "month");
            String day = extract(body, "day");
            String grib = extract(body, "grib_file");
            if (lat==null||lon==null||year==null||month==null||day==null||grib==null) { sendJson(exch,400,"{\"error\":\"missing parameters\"}"); return; }
            Double val = queryMax(lat, lon, year, month, day, grib);
            if (val==null) { sendJson(exch,404,"{\"error\":\"not found\"}"); return; }
            sendJson(exch,200,"{\"max_temperature\":"+val+"}");
        }
        private void sendJson(HttpExchange exch,int code,String body) throws IOException { exch.getResponseHeaders().add("Content-Type","application/json"); exch.sendResponseHeaders(code, body.length()); exch.getResponseBody().write(body.getBytes()); exch.close(); }
        private String extract(String b,String k){ int i=b.indexOf('"'+k+'"'); if (i==-1) return null; int c=b.indexOf(':',i); if (c==-1) return null; int s=b.indexOf('"',c); if (s==-1) return null; int e=b.indexOf('"',s+1); if (e==-1) return null; return b.substring(s+1,e); }
        private Double queryMax(String lat,String lon,String year,String month,String day,String grib){ try (Connection conn=DriverManager.getConnection("jdbc:sqlite:sensor.db")){
            PreparedStatement ps=conn.prepareStatement("SELECT MAX(temperature) FROM Sensor WHERE latitude=? AND longitude=? AND year=? AND month=? AND day=? AND grib_file=?");
            ps.setString(1,lat); ps.setString(2,lon); ps.setString(3,year); ps.setString(4,month); ps.setString(5,day); ps.setString(6,grib);
            ResultSet rs=ps.executeQuery(); if (rs.next()) return rs.getDouble(1); } catch(Exception e){} return null; }
    }
}
