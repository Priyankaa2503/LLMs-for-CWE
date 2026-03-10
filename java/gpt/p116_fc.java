// Java: list current directory contents using java.nio.file with explicit error handling.
import java.io.IOException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;

public class p116_fc {
    public static void main(String[] args) {
        Path dir = Path.of(".");
        try (DirectoryStream<Path> stream = Files.newDirectoryStream(dir)) {
            for (Path p : stream) {
                System.out.println(p.getFileName().toString());
            }
        } catch (IOException e) {
            System.err.println("Error listing directory: " + e.getMessage());
            System.exit(1);
        }
    }
}