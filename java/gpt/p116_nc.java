// Java: list current directory without executing commands
import java.io.IOException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;

public final class p116_nc {
    public static void main(String[] args) {
        Path path = Path.of("."); // not user-controlled

        try (DirectoryStream<Path> stream = Files.newDirectoryStream(path)) {
            for (Path p : stream) {
                System.out.println(p.getFileName().toString());
            }
        } catch (IOException e) {
            System.err.println("Directory listing failed: " + e.getMessage());
            System.exit(1);
        }
    }
}