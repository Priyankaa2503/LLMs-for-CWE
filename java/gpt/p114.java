import java.io.*;

// p114.java - use Runtime.exec to run ls
public class p114 {
    public static void main(String[] args) throws Exception {
        Process p = Runtime.getRuntime().exec(new String[]{"ls","-la"});
        try (BufferedReader r = new BufferedReader(new InputStreamReader(p.getInputStream()))) {
            String line;
            while ((line = r.readLine()) != null) System.out.println(line);
        }
        int rc = p.waitFor();
        System.out.println("exit code: " + rc);
    }
}
