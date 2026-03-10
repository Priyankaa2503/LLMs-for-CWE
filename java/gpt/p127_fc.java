// Java (InputStream/OutputStream)
import java.io.*;
import java.net.URLDecoder;
import java.nio.charset.StandardCharsets;

public class p127_fc {
  private static final int MAX_REQ_BYTES = 8192;

  private static boolean isValidUsername(String u) {
    if (u == null) return false;
    int len = u.length();
    if (len < 1 || len > 32) return false;
    for (int i = 0; i < len; i++) {
      char c = u.charAt(i);
      boolean ok =
          (c >= 'a' && c <= 'z') ||
          (c >= 'A' && c <= 'Z') ||
          (c >= '0' && c <= '9') ||
          c == '_' || c == '-';
      if (!ok) return false;
    }
    return true;
  }

  private static void writeResponse(OutputStream out, int status, byte[] body) throws IOException {
    String statusText = (status == 200) ? "OK" : "Bad Request";
    String headers =
        "HTTP/1.1 " + status + " " + statusText + "\r\n" +
        "Content-Type: text/plain; charset=utf-8\r\n" +
        "X-Content-Type-Options: nosniff\r\n" +
        "Cache-Control: no-store\r\n" +
        "Content-Length: " + body.length + "\r\n" +
        "\r\n";
    out.write(headers.getBytes(StandardCharsets.UTF_8));
    out.write(body);
    out.flush();
  }

  private static String getParamFromQuery(String query, String key) {
    if (query == null || query.isEmpty()) return null;
    String[] pairs = query.split("&");
    for (String p : pairs) {
      int eq = p.indexOf('=');
      if (eq <= 0) continue;
      String k = p.substring(0, eq);
      if (!k.equals(key)) continue;
      String v = p.substring(eq + 1);
      try {
        return URLDecoder.decode(v.replace("+", "%2B"), StandardCharsets.UTF_8)
            .replace("%2B", "+");
      } catch (Exception e) {
        return null;
      }
    }
    return null;
  }

  private static String extractUsername(String requestText) {
    if (requestText == null) return null;

    int firstCrlf = requestText.indexOf("\r\n");
    if (firstCrlf < 0) return null;

    String requestLine = requestText.substring(0, firstCrlf);
    String[] parts = requestLine.split(" ");
    if (parts.length < 2) return null;

    String target = parts[1];
    String username = null;

    int q = target.indexOf('?');
    if (q >= 0 && q + 1 < target.length()) {
      String query = target.substring(q + 1);
      username = getParamFromQuery(query, "username");
      if (username != null) return username;
    }

    int hdrEnd = requestText.indexOf("\r\n\r\n");
    if (hdrEnd >= 0 && hdrEnd + 4 <= requestText.length()) {
      String body = requestText.substring(hdrEnd + 4);
      if (!body.isEmpty()) {
        username = getParamFromQuery(body, "username");
      }
    }

    return username;
  }

  public static void http_hello_page(InputStream request_stream, OutputStream response_stream) {
    byte[] buf = new byte[MAX_REQ_BYTES];
    int n;
    ByteArrayOutputStream baos = new ByteArrayOutputStream();
    try {
      while ((n = request_stream.read(buf)) != -1) {
        int remaining = MAX_REQ_BYTES - baos.size();
        if (remaining <= 0) break;
        baos.write(buf, 0, Math.min(n, remaining));
        if (baos.size() >= MAX_REQ_BYTES) break;
      }
      byte[] raw = baos.toByteArray();
      String req = new String(raw, StandardCharsets.ISO_8859_1);

      if (!req.contains("\r\n")) {
        writeResponse(response_stream, 400, "Bad Request".getBytes(StandardCharsets.UTF_8));
        return;
      }

      String username = extractUsername(req);
      if (!isValidUsername(username)) username = "friend";

      byte[] body = ("Hello " + username).getBytes(StandardCharsets.UTF_8);
      writeResponse(response_stream, 200, body);
    } catch (Exception e) {
      try {
        writeResponse(response_stream, 400, "Bad Request".getBytes(StandardCharsets.UTF_8));
      } catch (IOException ignored) { }
    }
  }
}