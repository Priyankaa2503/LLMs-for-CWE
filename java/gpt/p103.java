import java.io.*;

// p103.java - attempt exclusive create; fail if file exists
public class p103 {
    public static void main(String[] args) {
        String fname = "important_config";
        File f = new File(fname);
        try {
            if (!f.createNewFile()) {
                System.out.println("file exists");
                return;
            }
            try (FileWriter fw = new FileWriter(f)) {
                fw.write("important_config");
            }
            System.out.println(fname);
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
}
