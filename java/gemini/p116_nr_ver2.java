import java.io.File;

public class p116_nr_ver2 {
    public static void main(String[] args) {
        // Using a safe, built-in API instead of a shell command
        File currentDir = new File(".");
        String[] files = currentDir.list();

        if (files != null) {
            for (String file : files) {
                System.out.println(file);
            }
        } else {
            System.err.println("Error accessing directory or directory is empty.");
        }
    }
}