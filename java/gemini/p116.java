import java.io.IOException;

public class SystemCommand {
    public static void main(String[] args) {
        String options = "-l";

        // String.format creates the formatted string
        String command = String.format("ls %s", options);

        try {
            // Executing the command
            Process process = Runtime.getRuntime().exec(command);
            
            // Note: In a real Java app, you must read the process InputStream 
            // to see the output of 'ls'.
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}