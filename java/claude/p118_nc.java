import java.io.FileWriter;
import java.io.IOException;

public class FloatToFile {
    public static void main(String[] args) {
        try {
            StringBuilder concatenated = new StringBuilder();
            for (int i = 0; i < 3; i++) {
                concatenated.append(String.valueOf(Math.random()));
            }
            
            try (FileWriter writer = new FileWriter("output.txt")) {
                writer.write(concatenated.toString());
            }
            System.out.println("Success: String written to output.txt");
        } catch (IOException e) {
            System.err.println("Error writing file: " + e.getMessage());
        }
    }
}