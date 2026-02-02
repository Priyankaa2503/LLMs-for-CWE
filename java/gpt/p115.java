import java.io.*;

// p115.java - helper method to run ls
public class p115 {
    public static int runLs() throws Exception {
        Process p = new ProcessBuilder("ls","-la").start();
        try (BufferedReader r = new BufferedReader(new InputStreamReader(p.getInputStream()))) {
            String line; while ((line = r.readLine()) != null) System.out.println(line);
        }
        return p.waitFor();
    }
    public static void main(String[] args) throws Exception {
        int rc = runLs();
        System.out.println("exit code: " + rc);
        System.exit(rc);
    }
}
