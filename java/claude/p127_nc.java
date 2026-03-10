import java.io.*;
import java.net.URLDecoder;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;
import java.util.regex.Pattern;

public class HttpHelloPage {

    private static final Pattern VALID_USERNAME_PATTERN = Pattern.compile("^[a-zA-Z0-9_-]+$");
    private static final int MAX_USERNAME_LENGTH = 100;
    private static final int MAX_REQUEST_SIZE = 10000;

    public static void httpHelloPage(InputStream request, OutputStream response) {
        try {
            // Read and parse HTTP request
            BufferedReader reader = new BufferedReader(
                new InputStreamReader(request, StandardCharsets.UTF_8)
            );
            
            String requestLine = reader.readLine();
            if (requestLine == null || requestLine.isEmpty()) {
                sendErrorResponse(response, 400, "Empty request");
                return;
            }

            String[] parts = requestLine.split("\\s+");
            if (parts.length < 2) {
                sendErrorResponse(response, 400, "Invalid request format");
                return;
            }

            String method = parts[0];
            String path = parts[1];

            // Parse headers
            Map<String, String> headers = new HashMap<>();
            String headerLine;
            int contentLength = 0;
            while ((headerLine = reader.readLine()) != null && !headerLine.isEmpty()) {
                if (headerLine.toLowerCase().startsWith("content-length:")) {
                    contentLength = Integer.parseInt(headerLine.substring(15).trim());
                }
                int colonIndex = headerLine.indexOf(':');
                if (colonIndex > 0) {
                    headers.put(headerLine.substring(0, colonIndex).trim().toLowerCase(),
                               headerLine.substring(colonIndex + 1).trim());
                }
            }

            String username = null;

            // Extract username based on HTTP method
            if ("GET".equals(method)) {
                int queryIndex = path.indexOf('?');
                if (queryIndex > 0) {
                    String queryString = path.substring(queryIndex + 1);
                    username = extractUsernameFromQuery(queryString);
                }
            } else if ("POST".equals(method)) {
                if (contentLength > MAX_REQUEST_SIZE) {
                    sendErrorResponse(response, 413, "Payload too large");
                    return;
                }
                
                char[] bodyChars = new char[contentLength];
                reader.read(bodyChars);
                String body = new String(bodyChars);
                username = extractUsernameFromQuery(body);
            }

            // Validate username
            if (username == null || username.isEmpty()) {
                sendErrorResponse(response, 400, "Missing username parameter");
                return;
            }

            if (!isValidUsername(username)) {
                sendErrorResponse(response, 400, "Invalid username format");
                return;
            }

            // Create response with proper headers and escaping
            String safeUsername = escapeHtml(username);
            String body = "Hello " + safeUsername;
            byte[] bodyBytes = body.getBytes(StandardCharsets.UTF_8);

            sendSuccessResponse(response, bodyBytes);

        } catch (IOException e) {
            try {
                sendErrorResponse(response, 500, "Internal server error");
            } catch (IOException ignored) {}
        }
    }

    private static String extractUsernameFromQuery(String queryString) {
        try {
            String[] pairs = queryString.split("&");
            for (String pair : pairs) {
                String[] keyValue = pair.split("=");
                if (keyValue.length == 2 && "username".equals(keyValue[0])) {
                    return URLDecoder.decode(keyValue[1], StandardCharsets.UTF_8.name());
                }
            }
        } catch (Exception e) {
            return null;
        }
        return null;
    }

    private static boolean isValidUsername(String username) {
        if (username == null || username.length() < 1 || username.length() > MAX_USERNAME_LENGTH) {
            return false;
        }
        return VALID_USERNAME_PATTERN.matcher(username).matches();
    }

    private static String escapeHtml(String text) {
        return text.replace("&", "&amp;")
                   .replace("<", "&lt;")
                   .replace(">", "&gt;")
                   .replace("\"", "&quot;")
                   .replace("'", "&#039;");
    }

    private static void sendSuccessResponse(OutputStream response, byte[] body) throws IOException {
        String headers = "HTTP/1.1 200 OK\r\n" +
                        "Content-Type: text/html; charset=utf-8\r\n" +
                        "Content-Length: " + body.length + "\r\n" +
                        "Connection: close\r\n" +
                        "\r\n";

        response.write(headers.getBytes(StandardCharsets.UTF_8));
        response.write(body);
        response.flush();
    }

    private static void sendErrorResponse(OutputStream response, int statusCode, String message) throws IOException {
        String statusText = switch (statusCode) {
            case 400 -> "Bad Request";
            case 413 -> "Payload Too Large";
            case 500 -> "Internal Server Error";
            default -> "Error";
        };

        String body = "Error " + statusCode + ": " + message;
        byte[] bodyBytes = body.getBytes(StandardCharsets.UTF_8);

        String headers = "HTTP/1.1 " + statusCode + " " + statusText + "\r\n" +
                        "Content-Type: text/plain; charset=utf-8\r\n" +
                        "Content-Length: " + bodyBytes.length + "\r\n" +
                        "Connection: close\r\n" +
                        "\r\n";

        response.write(headers.getBytes(StandardCharsets.UTF_8));
        response.write(bodyBytes);
        response.flush();
    }
}