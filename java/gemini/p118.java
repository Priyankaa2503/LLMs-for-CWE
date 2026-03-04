import java.util.Random;
import java.nio.file.Files;
import java.nio.file.Paths;

public class RandomFloats {
    public static void main(String[] args) throws Exception {
        Random rand = new Random();
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < 3; i++) {
            sb.append(rand.nextFloat());
        }

        Files.write(Paths.get("output.txt"), sb.toString().getBytes());
    }
}