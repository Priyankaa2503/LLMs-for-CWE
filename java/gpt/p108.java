import java.io.*;

// p108.java - run `getent passwd <username>` and print output
public class p108 {
    public static void main(String[] args) throws Exception {
        if (args.length < 1) { System.err.println("usage: p108 <username>"); System.exit(1); }
        String user = args[0];
        ProcessBuilder pb = new ProcessBuilder("getent", "passwd", user);
        pb.redirectErrorStream(true);
        Process p = pb.start();
        try (BufferedReader r = new BufferedReader(new InputStreamReader(p.getInputStream()))) {
            String line;
            while ((line = r.readLine()) != null) System.out.println(line);
        }
        int rc = p.waitFor();
        System.exit(rc);
    }
}
