import java.io.*;

public class Handler {
    public void httpHelloPage(InputStream request, OutputStream response) throws IOException {
        // Read username from request stream
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String username = reader.readLine();

        // Construct response
        String greeting = "Hello " + (username != null ? username : "Guest");

        // Write to response stream
        PrintWriter writer = new PrintWriter(response, true);
        writer.print(greeting);
        writer.flush();
    }
}