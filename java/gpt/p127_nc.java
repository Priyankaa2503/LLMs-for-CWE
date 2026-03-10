// Java (InputStream/OutputStream)
import java.io.*;
import java.net.URLDecoder;
import java.nio.charset.StandardCharsets;
import java.util.*;
import java.util.regex.Pattern;

public final class p127_nc {
  private static final int MAX_REQ_BYTES = 8192;
  private static final int MAX_USER_LEN = 32;
  private static final Pattern USERNAME_RE = Pattern.compile("^[A-Za-z0-9_-]{1,32}$");

  private static String htmlEscape(String s) {
    StringBuilder out = new StringBuilder(Math.min(256, s.length() + 16));
    for (int i = 0; i < s.length(); i++) {
      char c = s.charAt(i);
      switch (c) {
        case '&': out.append("&amp;"); break;
        case '<': out.append("&lt;"); break;
        case '>': out.append("&gt;"); break;
        case '"': out.append("&quot;"); break;
        case '\'': out.append("&#39;"); break;
        default: out.append(c);
      }
    }
    return out.toString();
  }

  private static void writeResponse(OutputStream resp, int status, String reason, String body) throws IOException {
    byte[] bodyBytes = body.getBytes(StandardCharsets.UTF_8);
    String headers =
        "HTTP/1.1 " + status + " " + reason + "\r\n" +
        "Content-Type: text/html; charset=utf-8\r\n" +
        "X-Content-Type-Options: nosniff\r\n" +
        "Content-Length: " + bodyBytes.length + "\r\n" +
        "Connection: close\r\n" +
        "\r\n";
    resp.write(headers.getBytes(StandardCharsets.US_ASCII));
    resp.write(bodyBytes);
    resp.flush();
  }

  private static byte[] readUpTo(InputStream in, int maxBytes) throws IOException {
    ByteArrayOutputStream baos = new ByteArrayOutputStream();
    byte[] buf = new byte[1024];
    int total = 0;
    while (total < maxBytes) {
      int toRead = Math.min(buf.length, maxBytes - total);
      int n = in.read(buf, 0, toRead);
      if (n == -1) break;
      baos.write(buf, 0, n);
      total += n;
    }
    return baos.toByteArray();
  }

  private static String extractUsername(String reqText) {
    String[] lines = reqText.split("\\r?\\n", -1);
    String first = lines.length > 0 ? lines[0] : "";
    String[] parts = first.split(" ");
    if (parts.length >= 2) {
      String path = parts[1];
      int q = path.indexOf('?');
      if (q >= 0 && q + 1 < path.length()) {
        String qs = path.substring(q + 1);
        String u = parseFormField(qs, "username");
        if (u != null) return u;
      }
    }

    String split = reqText.contains("\r\n\r\n") ? "\r\n\r\n" : "\n\n";
    String body = reqText.contains(split) ? reqText.split(Pattern.quote(split), 2)[1] : reqText;
    return parseFormField(body, "username");
  }

  private static String parseFormField(String data, String key) {
    String[] pairs = data.split("&");
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

  private static boolean validUsername(String u) {
    if (u == null) return false;
    if (u.length() == 0 || u.length() > MAX_USER_LEN) return false;
    return USERNAME_RE.matcher(u).matches();
  }

  // request: raw HTTP request stream from client
  // response: raw HTTP response stream to client
  public static void http_hello_page(InputStream request, OutputStream response) {
    try {
      if (request == null || response == null) return;

      byte[] reqBytes = readUpTo(request, MAX_REQ_BYTES);
      String reqText = new String(reqBytes, StandardCharsets.UTF_8);

      String username = extractUsername(reqText);
      if (!validUsername(username)) {
        writeResponse(response, 400, "Bad Request", "<!doctype html><html><body>Bad Request</body></html>");
        return;
      }

      String safe = htmlEscape(username);
      String body = "<!doctype html><html><body>Hello " + safe + "</body></html>";
      writeResponse(response, 200, "OK", body);
    } catch (IOException e) {
      try {
        writeResponse(response, 500, "Internal Server Error", "<!doctype html><html><body>Server Error</body></html>");
      } catch (IOException ignored) {}
    }
  }
}