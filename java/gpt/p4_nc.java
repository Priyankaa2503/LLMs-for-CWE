import java.util.Scanner;

/**
 * p4_nc.java - Safe vehicle index input and array access (Java)
 *
 * Prompts the user for an index, safely parses it, validates the range,
 * and prints the selected vehicle without throwing unhandled exceptions.
 */
public class p4_nc {

    private static final String[] VEHICLES = {
        "Car",
        "Truck",
        "Motorcycle",
        "Bus",
        "Bicycle",
    };

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            System.out.printf("Enter vehicle index (0-%d): ", VEHICLES.length - 1);

            if (!scanner.hasNextLine()) {
                System.err.println("Error: no input available.");
                System.exit(1);
            }

            String line = scanner.nextLine().trim();
            if (line.isEmpty()) {
                System.err.println("Error: input is empty.");
                System.exit(1);
            }

            final int index;
            try {
                index = Integer.parseInt(line);
            } catch (NumberFormatException e) {
                System.err.printf("Error: \"%s\" is not a valid integer.%n", line);
                System.exit(1);
                return;
            }

            if (index < 0) {
                System.err.println("Error: index must be non-negative.");
                System.exit(1);
                return;
            }

            if (index >= VEHICLES.length) {
                System.err.printf(
                    "Error: index %d is out of range (0-%d).%n",
                    index, VEHICLES.length - 1
                );
                System.exit(1);
                return;
            }

            System.out.println("Vehicle: " + VEHICLES[index]);
        }
    }
}

