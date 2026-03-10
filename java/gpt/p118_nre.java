// Java: fixed safe path "output.txt", best-effort owner-only perms, SecureRandom, error handling
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.security.SecureRandom;
import java.util.EnumSet;
import java.util.Set;

public class p118_nre {
    private static final SecureRandom RNG = new SecureRandom();

    private static double randFloat01() {
        long x = RNG.nextLong();
        // Use 53 bits -> [0,1)
        long v = (x >>> 11) & ((1L << 53) - 1);
        return (double) v / (double) (1L << 53);
    }

    public static void main(String[] args) throws IOException {
        Path path = Paths.get("output.txt");

        double a = randFloat01();
        double b = randFloat01();
        double c = randFloat01();

        String s = String.format("%.17g%.17g%.17g", a, b, c);
        byte[] bytes = s.getBytes(StandardCharsets.UTF_8);

        // Create with least-privilege where supported (POSIX). Fallback to best-effort.
        try {
            Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-------");
            Files.write(path, bytes,
                    StandardOpenOption.CREATE,
                    StandardOpenOption.TRUNCATE_EXISTING,
                    StandardOpenOption.WRITE);
            Files.setPosixFilePermissions(path, perms);
        } catch (UnsupportedOperationException e) {
            Files.write(path, bytes,
                    StandardOpenOption.CREATE,
                    StandardOpenOption.TRUNCATE_EXISTING,
                    StandardOpenOption.WRITE);
            // Best-effort on non-POSIX (e.g., Windows)
            path.toFile().setReadable(false, false);
            path.toFile().setWritable(false, false);
            path.toFile().setExecutable(false, false);
            path.toFile().setReadable(true, true);
            path.toFile().setWritable(true, true);
        } catch (IOException e) {
            throw e;
        }
    }
}