import java.io.*;

// p105.java - create secret.txt and write base64 string; set owner-only perms (best-effort)
public class p105 {
    public static void main(String[] args) {
        String fname = "secret.txt";
        String msg = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        try (FileWriter fw = new FileWriter(fname)) { fw.write(msg); }
        catch (IOException e) { e.printStackTrace(); System.exit(1); }
        File f = new File(fname);
        f.setReadable(true, true);
        f.setWritable(true, true);
        System.out.println(fname);
    }
}
