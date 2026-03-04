import java.io.*;

public class WebHandler {
    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(response, true);

        // Read username from stream
        String username = reader.readLine();
        
        // Escape and write
        String safeUsername = escape_html(username);
        writer.print("hello " + safeUsername);
        writer.flush();
    }
}