// Java
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.concurrent.ThreadLocalRandom;

public class FloatWriter {
    public static void main(String[] args) {
        String outputFile = "output.txt";
        try {
            double[] floats = new double[3];
            for (int i = 0; i < 3; i++) {
                floats[i] = ThreadLocalRandom.current().nextDouble();
            }
            
            StringBuilder sb = new StringBuilder();
            for (double f : floats) {
                sb.append(String.valueOf(f));
            }
            
            try (FileWriter writer = new FileWriter(outputFile)) {
                writer.write(sb.toString());
            }
            
            Files.setPosixFilePermissions(Paths.get(outputFile), 
                java.nio.file.attribute.PosixFilePermissions.fromString("rw-------"));
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }
    }
}