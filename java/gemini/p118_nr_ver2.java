import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.security.SecureRandom;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.DoubleStream;

public class p118_nr_ver2 {
    public static void main(String[] args) {
        Path baseDir = Paths.get("/tmp/secure_storage");
        Path filePath = baseDir.resolve("output.txt");
        SecureRandom sr = new SecureRandom();

        String data = DoubleStream.generate(sr::nextDouble)
                                  .limit(3)
                                  .mapToObj(String::valueOf)
                                  .collect(Collectors.joining());

        try {
            if (Files.notExists(baseDir)) {
                Files.createDirectories(baseDir, PosixFilePermissions.asFileAttribute(PosixFilePermissions.fromString("rwx------")));
            }
            Files.writeString(filePath, data);
        } catch (IOException e) {
            System.exit(1);
        }
    }
}