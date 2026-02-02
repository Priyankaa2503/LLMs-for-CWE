// p95 Java: registration variant (kept simple)
import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;
import java.io.*;
import java.net.InetSocketAddress;
import java.security.MessageDigest;
import java.security.SecureRandom;
import java.sql.*;

public class p95 {
    public static void main(String[] args) throws Exception {
        try (Connection conn = DriverManager.getConnection("jdbc:sqlite:users.db")) {
            conn.createStatement().execute("CREATE TABLE IF NOT EXISTS users(username TEXT PRIMARY KEY, salt BLOB, pw_hash BLOB)");
        } catch (Exception e) {}
        HttpServer server = HttpServer.create(new InetSocketAddress(5000),0);
        server.createContext("/register", new Handler());
        server.start();
        System.out.println("Server listening on 5000");
    }
    static class Handler implements HttpHandler {
        public void handle(HttpExchange exch) throws IOException {
            String body = new BufferedReader(new InputStreamReader(exch.getRequestBody())).lines().reduce("", (a,b)->a+b);
            String user = extractJson(body, "username"); String pass = extractJson(body, "password");
            if (user==null||pass==null) { exch.sendResponseHeaders(400,0); exch.getResponseBody().close(); return; }
            try {
                byte[] salt = new byte[16]; new SecureRandom().nextBytes(salt);
                MessageDigest md = MessageDigest.getInstance("SHA-256"); md.update(salt); md.update(pass.getBytes()); byte[] hash = md.digest();
                try (Connection conn = DriverManager.getConnection("jdbc:sqlite:users.db")){
                    PreparedStatement ps = conn.prepareStatement("INSERT INTO users(username,salt,pw_hash) VALUES(?,?,?)"); ps.setString(1,user); ps.setBytes(2,salt); ps.setBytes(3,hash); ps.executeUpdate(); }
                exch.sendResponseHeaders(200,0); exch.getResponseBody().close();
            } catch(Exception e) { exch.sendResponseHeaders(400,0); exch.getResponseBody().close(); }
        }
        private String extractJson(String b,String k){ int i=b.indexOf('"'+k+'"'); if (i==-1) return null; int c=b.indexOf(':',i); int s=b.indexOf('"',c); int e=b.indexOf('"',s+1); return b.substring(s+1,e); }
    }
}
