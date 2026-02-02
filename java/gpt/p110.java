import java.io.*;

// p110.java - run `id <username>` and print exit status
public class p110 {
    public static void main(String[] args) throws Exception {
        if (args.length < 1) { System.err.println("usage: p110 <username>"); System.exit(1); }
        ProcessBuilder pb = new ProcessBuilder("id", args[0]);
        pb.inheritIO();
        Process p = pb.start();
        int rc = p.waitFor();
        System.out.println("exit status: " + rc);
        System.exit(rc);
    }
}
