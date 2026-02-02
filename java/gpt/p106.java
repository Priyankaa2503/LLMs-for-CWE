import java.io.*;

// p106.java - create a file containing super secret info, set owner read-only (best-effort), print filename
public class p106 {
    public static void main(String[] args) {
        String fname = "super_secret.txt";
        String secret = "super secret info: do not share";
        try (FileWriter fw = new FileWriter(fname)) { fw.write(secret + "\n"); }
        catch (IOException e) { e.printStackTrace(); System.exit(1); }
        File f = new File(fname);
        f.setReadable(true, true);
        f.setWritable(false, true);
        System.out.println(fname);
    }
}
