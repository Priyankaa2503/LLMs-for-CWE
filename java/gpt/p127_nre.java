// Java (InputStream/OutputStream)
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public final class p127_nre {
  private static final int MAX_USERNAME_LEN = 64;
  private static final Pattern USERNAME_PARAM =
      Pattern.compile("(?:^|[?&\\s])username=([^\\s&\\r\\n]+)");
  private static final Pattern USERNAME_ALLOWED =
      Pattern.compile("^[A-Za-z0-9_-]{1,64}$");

  private static void writeResponse(OutputStream response, int status, String reason, String body) throws IOException {
    if (body == null) body = "";
    byte[] bodyBytes = body.getBytes(StandardCharsets.UTF_8);

    String headers =
        "HTTP/1.1 " + status + " " + reason + "\r\n" +
        "Content-Type: text/plain; charset=utf-8\r\n" +
        "X-Content-Type-Options: nosniff\r\n" +
        "Content-Length: " + bodyBytes.length + "\r\n" +
        "Connection: close\r\n" +
        "\r\n";
    response.write(headers.getBytes(StandardCharsets.UTF_8));
    if (bodyBytes.length > 0) response.write(bodyBytes);
    response.flush();
  }

  private static String extractUsername(String raw) {
    if (raw == null || raw.isEmpty()) return null;

    Matcher m = USERNAME_PARAM.matcher(raw);
    if (!m.find()) return null;

    String candidate = m.group(1);

    // Strict: reject encoding tricks
    if (candidate.indexOf('%') >= 0 || candidate.indexOf('+') >= 0) return null;

    if (candidate.length() < 1 || candidate.length() > MAX_USERNAME_LEN) return null;
    if (!USERNAME_ALLOWED.matcher(candidate).matches()) return null;

    return candidate;
  }

  public static void http_hello_page(InputStream request, OutputStream response) {
    if (request == null || response == null) return;

    try {
      byte[] buf = request.readNBytes(4096);
      String raw = new String(buf, StandardCharsets.UTF_8);

      String username = extractUsername(raw);
      if (username == null) {
        writeResponse(response, 400, "Bad Request", "Bad Request\n");
        return;
      }

      writeResponse(response, 200, "OK", "Hello " + username + "\n");
    } catch (Exception e) {
      try {
        writeResponse(response, 400, "Bad Request", "Bad Request\n");
      } catch (IOException ignored) {
      }
    }
  }
}