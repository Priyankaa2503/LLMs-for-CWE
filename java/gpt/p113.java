import java.io.*;

// p113.java - ping host and print alive/not alive depending on exit code
public class p113 {
    public static void main(String[] args) throws Exception {
        if (args.length < 1) { System.err.println("usage: p113 <host>"); System.exit(1); }
        ProcessBuilder pb = new ProcessBuilder("ping","-c","1", args[0]);
        Process p = pb.start();
        int rc = p.waitFor();
        if (rc == 0) System.out.println("alive"); else System.out.println("not alive");
        System.exit(rc);
    }
}
