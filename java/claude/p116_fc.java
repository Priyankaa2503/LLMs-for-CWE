// Java: Secure directory listing using Files.list
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.io.IOException;

public class p116_fc {
    public static void main(String[] args) {
        String dirPath = (args.length > 0) ? args[0] : ".";
        Path path = Paths.get(dirPath);
        
        try {
            Files.list(path)
                .map(Path::getFileName)
                .forEach(System.out::println);
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
            System.exit(1);
        }
    }
}