// Java 17+
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.security.SecureRandom;
import java.util.Locale;

public class p118_fc {
    private static final Path ALLOWLIST_DIR = Paths.get("safe_out").toAbsolutePath().normalize();
    private static final String FILENAME = "floats.txt";
    private static final String DELIM = "|";

    public static void main(String[] args) {
        try {
            Files.createDirectories(ALLOWLIST_DIR);
        } catch (IOException e) {
            System.err.println("mkdir failed: " + e.getMessage());
            System.exit(1);
        }

        Path outPath = ALLOWLIST_DIR.resolve(FILENAME).normalize();

        // Prevent path traversal / escape from allowlisted directory
        if (!outPath.getParent().equals(ALLOWLIST_DIR)) {
            System.err.println("refusing to write outside allowlisted directory");
            System.exit(1);
        }

        SecureRandom rng = new SecureRandom(); // crypto-secure PRNG
        double a = rng.nextDouble(); // [0.0, 1.0)
        double b = rng.nextDouble();
        double c = rng.nextDouble();

        String sA = String.format(Locale.ROOT, "%.8f", a);
        String sB = String.format(Locale.ROOT, "%.8f", b);
        String sC = String.format(Locale.ROOT, "%.8f", c);
        String line = sA + DELIM + sB + DELIM + sC + "\n";

        try {
            // Best-effort symlink safety: avoid following symlinks when writing the final file
            // by writing to a temp file in the allowlisted dir and atomically moving it in place.
            Path tmp = Files.createTempFile(ALLOWLIST_DIR, "floats-", ".tmp");
            Files.writeString(tmp, line, StandardCharsets.UTF_8,
                    StandardOpenOption.TRUNCATE_EXISTING);

            // Atomic replace within same directory
            Files.move(tmp, outPath,
                    StandardCopyOption.REPLACE_EXISTING,
                    StandardCopyOption.ATOMIC_MOVE);
        } catch (IOException e) {
            System.err.println("write failed: " + e.getMessage());
            System.exit(1);
        }
    }
}