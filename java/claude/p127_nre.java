import java.io.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.net.URLDecoder;
import java.nio.charset.StandardCharsets;

public class HttpHelloPage {
    
    public static void httpHelloPage(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(
            new InputStreamReader(request, StandardCharsets.UTF_8));
        
        try {
            StringBuilder requestData = new StringBuilder();
            String line;
            int maxSize = 4096;
            int totalBytes = 0;
            
            while ((line = reader.readLine()) != null && totalBytes < maxSize) {
                requestData.append(line).append("\n");
                totalBytes += line.length();
            }
            
            String username = "";
            Pattern pattern = Pattern.compile("username=([^&\\s\\r\\n]+)");
            Matcher matcher = pattern.matcher(requestData.toString());
            
            if (matcher.find()) {
                username = URLDecoder.decode(matcher.group(1), StandardCharsets.UTF_8);
            }
            
            // Validate: length and allowed characters
            if (username.length() > 255) {
                username = username.substring(0, 255);
            }
            
            username = username.replaceAll("[^a-zA-Z0-9_-]", "");
            
            // Response with text/plain
            String responseText = "Hello " + username;
            byte[] responseBytes = responseText.getBytes(StandardCharsets.UTF_8);
            
            String headers = "HTTP/1.1 200 OK\r\n" +
                           "Content-Type: text/plain; charset=utf-8\r\n" +
                           "Content-Length: " + responseBytes.length + "\r\n" +
                           "Connection: close\r\n" +
                           "\r\n";
            
            response.write(headers.getBytes(StandardCharsets.UTF_8));
            response.write(responseBytes);
            response.flush();
            
        } catch (Exception e) {
            String errorResponse = "HTTP/1.1 400 Bad Request\r\n" +
                                 "Content-Type: text/plain; charset=utf-8\r\n" +
                                 "Connection: close\r\n" +
                                 "\r\n" +
                                 "Malformed request";
            response.write(errorResponse.getBytes(StandardCharsets.UTF_8));
            response.flush();
        } finally {
            reader.close();
        }
    }
}