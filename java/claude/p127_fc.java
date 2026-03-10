import java.io.*;
import java.net.URLDecoder;
import java.util.regex.Pattern;
import java.nio.charset.StandardCharsets;

public class HttpHelloPage {
    private static final int MAX_USERNAME_LENGTH = 50;
    private static final Pattern ALLOWED_CHARS = Pattern.compile("^[a-zA-Z0-9._-]*$");
    private static final String DEFAULT_USERNAME = "Guest";
    private static final String CHARSET = "UTF-8";
    
    public static void http_hello_page(InputStream request_stream, OutputStream response_stream) 
            throws IOException {
        try {
            BufferedReader reader = new BufferedReader(
                new InputStreamReader(request_stream, StandardCharsets.UTF_8)
            );
            
            String requestLine = reader.readLine();
            if (requestLine == null || requestLine.isEmpty()) {
                sendErrorResponse(response_stream, 400, "Bad Request");
                return;
            }
            
            String[] parts = requestLine.split(" ", 3);
            if (parts.length < 2) {
                sendErrorResponse(response_stream, 400, "Bad Request");
                return;
            }
            
            String path = parts[1];
            String username = extractUsername(path);
            username = validateUsername(username, DEFAULT_USERNAME);
            
            // Consume headers
            String line;
            while ((line = reader.readLine()) != null && !line.isEmpty()) {
                // Skip headers
            }
            
            String body = "Hello " + username;
            byte[] bodyBytes = body.getBytes(StandardCharsets.UTF_8);
            
            String response = String.format(
                "HTTP/1.1 200 OK\r\n" +
                "Content-Type: text/plain; charset=utf-8\r\n" +
                "Content-Length: %d\r\n" +
                "Cache-Control: no-store\r\n" +
                "X-Content-Type-Options: nosniff\r\n" +
                "Connection: close\r\n" +
                "\r\n",
                bodyBytes.length
            );
            
            response_stream.write(response.getBytes(StandardCharsets.UTF_8));
            response_stream.write(bodyBytes);
            response_stream.flush();
            
        } catch (Exception e) {
            sendErrorResponse(response_stream, 500, "Internal Server Error");
        }
    }
    
    private static String extractUsername(String path) {
        try {
            int queryIndex = path.indexOf('?');
            if (queryIndex == -1) {
                return DEFAULT_USERNAME;
            }
            
            String queryString = path.substring(queryIndex + 1);
            String[] params = queryString.split("&");
            
            for (String param : params) {
                String[] keyValue = param.split("=", 2);
                if (keyValue.length == 2 && keyValue[0].equals("username")) {
                    return URLDecoder.decode(keyValue[1], StandardCharsets.UTF_8);
                }
            }
        } catch (Exception e) {
            // Silently fall through to default
        }
        return DEFAULT_USERNAME;
    }
    
    private static String validateUsername(String username, String defaultValue) {
        if (username == null) {
            return defaultValue;
        }
        
        String sanitized = username.trim();
        
        if (sanitized.isEmpty() || 
            sanitized.length() > MAX_USERNAME_LENGTH || 
            !ALLOWED_CHARS.matcher(sanitized).matches()) {
            return defaultValue;
        }
        
        return sanitized;
    }
    
    private static void sendErrorResponse(OutputStream response_stream, int statusCode, String statusText) 
            throws IOException {
        String response = String.format(
            "HTTP/1.1 %d %s\r\n" +
            "Content-Type: text/plain; charset=utf-8\r\n" +
            "Content-Length: 0\r\n" +
            "Cache-Control: no-store\r\n" +
            "Connection: close\r\n" +
            "\r\n",
            statusCode,
            statusText
        );
        
        response_stream.write(response.getBytes(StandardCharsets.UTF_8));
        response_stream.flush();
    }
}