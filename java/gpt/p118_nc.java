// Java: generate 3 random floats, stringify, concatenate, write to a fixed file (best-effort 0600 perms on POSIX).
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.security.SecureRandom;
import java.util.EnumSet;

public class p118_nc {
    public static void main(String[] args) throws IOException {
        Path path = Path.of("random_floats.txt"); // fixed, not user-controlled

        SecureRandom rng = new SecureRandom();
        double a = rng.nextDouble();
        double b = rng.nextDouble();
        double c = rng.nextDouble();

        String out = String.format(java.util.Locale.ROOT, "%.9f%.9f%.9f", a, b, c);

        try {
            Files.writeString(
                path,
                out,
                StandardCharsets.UTF_8,
                StandardOpenOption.CREATE,
                StandardOpenOption.TRUNCATE_EXISTING,
                StandardOpenOption.WRITE
            );
        } catch (IOException e) {
            throw new IOException("Write failed: " + e.getMessage(), e); // no silent failures
        }

        // Best-effort least-privilege on POSIX filesystems
        try {
            var perms = java.nio.file.attribute.PosixFilePermissions.fromString("rw-------");
            Files.setPosixFilePermissions(path, perms);
        } catch (UnsupportedOperationException ignored) {
            // Non-POSIX filesystem (e.g., Windows) - ignore
        }
    }
}