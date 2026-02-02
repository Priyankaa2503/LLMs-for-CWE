import java.io.*;

// p102.java - open important_config for read/write (create if missing), write, set 0644
public class p102 {
    public static void main(String[] args) {
        String fname = "important_config";
        String msg = "important_config";
        try (RandomAccessFile raf = new RandomAccessFile(fname, "rw")) {
            raf.setLength(0);
            raf.write(msg.getBytes("UTF-8"));
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
        File f = new File(fname);
        f.setReadable(true, false); // owner and others/group according to platform; best-effort
        f.setWritable(true, true);
        System.out.println(fname);
    }
}
