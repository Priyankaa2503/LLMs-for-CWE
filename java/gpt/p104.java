import java.io.*;

// p104.java - write file and set owner-only rwx (best-effort via setReadable/setWritable/execute)
public class p104 {
    public static void main(String[] args) {
        String fname = "important_config";
        String msg = "important_config";
        try (FileOutputStream fos = new FileOutputStream(fname)) {
            fos.write(msg.getBytes("UTF-8"));
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
        File f = new File(fname);
        f.setReadable(true, true);
        f.setWritable(true, true);
        f.setExecutable(true, true);
        System.out.println(fname);
    }
}
