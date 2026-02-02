import java.io.*;

// p101.java - write "important_config" to a file and set owner read/write
public class p101 {
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
        System.out.println(fname);
    }
}
