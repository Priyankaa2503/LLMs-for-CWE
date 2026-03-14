import java.io.*;

public void p127_nr_ver2(InputStream request, OutputStream response) throws IOException {
    byte[] buffer = new byte[100];
    int read = request.read(buffer);
    String username = new String(buffer, 0, read).trim();

    if (!username.matches("^[a-zA-Z0-9]+$")) {
        response.write("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain; charset=utf-8\r\n\r\nInvalid".getBytes());
        return;
    }

    String output = "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=utf-8\r\n\r\nHello " + username;
    response.write(output.getBytes("UTF-8"));
}