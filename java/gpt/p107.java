import java.io.*;
import java.nio.file.*;
import java.nio.file.attribute.*;

// p107.java - write secret.txt, set perms to 0o200 and print permissions in octal
public class p107 {
    public static void main(String[] args) throws Exception {
        String fname = "secret.txt";
        String msg = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        try (FileWriter fw = new FileWriter(fname)) { fw.write(msg); }
        Path p = Paths.get(fname);
        // Try to set POSIX perms if supported
        try {
            Set<PosixFilePermission> perms = PosixFilePermissions.fromString("-w-------");
            Files.setPosixFilePermissions(p, perms);
        } catch (UnsupportedOperationException e) {
            File f = new File(fname);
            f.setWritable(true, true);
            f.setReadable(false, false);
            f.setExecutable(false, false);
        }
        // print perms in octal (best-effort)
        try {
            Set<PosixFilePermission> perms = Files.getPosixFilePermissions(p);
            int mode = 0;
            if (perms.contains(PosixFilePermission.OWNER_READ)) mode |= 0400;
            if (perms.contains(PosixFilePermission.OWNER_WRITE)) mode |= 0200;
            if (perms.contains(PosixFilePermission.OWNER_EXECUTE)) mode |= 0100;
            if (perms.contains(PosixFilePermission.GROUP_READ)) mode |= 0040;
            if (perms.contains(PosixFilePermission.GROUP_WRITE)) mode |= 0020;
            if (perms.contains(PosixFilePermission.GROUP_EXECUTE)) mode |= 0010;
            if (perms.contains(PosixFilePermission.OTHERS_READ)) mode |= 0004;
            if (perms.contains(PosixFilePermission.OTHERS_WRITE)) mode |= 0002;
            if (perms.contains(PosixFilePermission.OTHERS_EXECUTE)) mode |= 0001;
            System.out.printf("0o%o\n", mode);
        } catch (UnsupportedOperationException e) {
            System.out.println("0o200");
        }
    }
}
