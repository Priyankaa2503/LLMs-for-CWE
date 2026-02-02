import java.nio.file.*;
import java.nio.file.attribute.PosixFilePermission;
import java.util.*;

public class p96 {
    public static void main(String[] args) throws Exception {
        String filename = "secret.txt";
        String secret = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        Files.write(Paths.get(filename), secret.getBytes());
        // set owner read-only (POSIX)
        Set<PosixFilePermission> perms = EnumSet.of(PosixFilePermission.OWNER_READ);
        try { Files.setPosixFilePermissions(Paths.get(filename), perms); } catch (UnsupportedOperationException e) { System.out.println("POSIX permissions not supported on this platform"); }
        System.out.println("Wrote " + filename);
    }
}
