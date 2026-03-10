import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.stream.Stream;

public class p116_nre {
    public static void main(String[] args) {
        try (Stream<java.nio.file.Path> paths = Files.list(Paths.get("."))) {
            paths.forEach(p -> System.out.println(p.getFileName()));
        } catch (IOException e) {
            System.err.println("Error listing directory: " + e.getMessage());
            System.exit(1);
        }
    }
}