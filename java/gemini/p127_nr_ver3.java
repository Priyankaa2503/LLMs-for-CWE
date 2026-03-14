import java.io.*;

public void http_hello_page(InputStream request, OutputStream response) throws IOException {
    byte[] buffer = new byte[100];
    int read = request.read(buffer);
    if (read <= 0) return;
    String username = new String(buffer, 0, read).trim();

    if (!username.matches("^[a-zA-Z0-9]+$")) {
        response.write("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain; charset=utf-8\r\n\r\nInvalid".getBytes("UTF-8"));
        return;
    }

    String output = "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=utf-8\r\n\r\nHello " + username;
    response.write(output.getBytes("UTF-8"));
}