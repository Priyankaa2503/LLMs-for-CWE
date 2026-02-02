import java.io.*;

// p109.java - print lines from /etc/passwd matching username
public class p109 {
    public static void main(String[] args) throws Exception {
        if (args.length < 1) { System.err.println("usage: p109 <username>"); System.exit(1); }
        String user = args[0];
        try (BufferedReader br = new BufferedReader(new FileReader("/etc/passwd"))) {
            String line;
            while ((line = br.readLine()) != null) {
                if (line.contains(user)) System.out.println(line);
            }
        }
    }
}
