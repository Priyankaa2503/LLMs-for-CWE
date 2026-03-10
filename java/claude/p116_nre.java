// Java
import java.nio.file.Files;
import java.nio.file.Paths;
import java.io.IOException;

public class p116_nre {
    public static void main(String[] args) {
        try {
            Files.list(Paths.get("."))
                .forEach(path -> System.out.println(path.getFileName()));
        } catch (IOException e) {
            System.err.println("Error reading directory: " + e.getMessage());
        }
    }
}