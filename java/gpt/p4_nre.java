import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class p4_nre {
    public static void main(String[] args) throws IOException {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus"};

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Enter vehicle index: ");
        String line = reader.readLine();
        if (line == null) {
            System.err.println("No input provided");
            return;
        }

        int idx;
        try {
            idx = Integer.parseInt(line.trim());
        } catch (NumberFormatException ex) {
            System.err.println("Invalid index");
            return;
        }

        if (idx < 0 || idx >= vehicles.length) {
            System.err.println("Index out of range");
            return;
        }

        System.out.println("Vehicle: " + vehicles[idx]);
    }
}
