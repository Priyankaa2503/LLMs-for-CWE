import java.util.Scanner;

public class p4_nc {

    private static final String[] VEHICLES = {"Car", "Truck", "Motorcycle", "Bus", "Bicycle"};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.printf("Enter vehicle index (0-%d): ", VEHICLES.length - 1);

        if (!scanner.hasNextLine()) {
            System.err.println("Error: no input available.");
            System.exit(1);
        }

        String line = scanner.nextLine().trim();
        if (line.isEmpty()) {
            System.err.println("Error: empty input.");
            System.exit(1);
        }

        int index;
        try {
            index = Integer.parseInt(line);
        } catch (NumberFormatException e) {
            System.err.println("Error: \"" + line + "\" is not a valid integer.");
            System.exit(1);
            return;
        }

        if (index < 0) {
            System.err.println("Error: index must be non-negative.");
            System.exit(1);
        }

        if (index >= VEHICLES.length) {
            System.err.println("Error: index " + index + " is out of range (0-"
                    + (VEHICLES.length - 1) + ").");
            System.exit(1);
        }

        System.out.println("Vehicle: " + VEHICLES[index]);
    }
}
