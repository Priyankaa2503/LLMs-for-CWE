// Java - Using Files API (secure alternative to system())
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.stream.Stream;

public class p116_nc {
    public static void main(String[] args) {
        String directory = ".";
        
        try (Stream<java.nio.file.Path> paths = Files.list(Paths.get(directory))) {
            paths.sorted()
                .forEach(path -> System.out.println(path.getFileName()));
        } catch (IOException e) {
            System.err.println("Error listing directory: " + e.getMessage());
            System.exit(1);
        }
    }
}