import java.util.Scanner;

public class p4_nre {

    private static final String[] VEHICLES = {
        "Sedan", "SUV", "Truck", "Motorcycle", "Van"
    };

    public static void main(String[] args) {
        System.out.println("Available vehicles (0-" + (VEHICLES.length - 1) + "):");
        for (int i = 0; i < VEHICLES.length; i++) {
            System.out.println("  [" + i + "] " + VEHICLES[i]);
        }

        System.out.print("\nEnter vehicle index: ");
        System.out.flush();

        Scanner scanner = new Scanner(System.in);

        /* Read the entire line as a string first */
        if (!scanner.hasNextLine()) {
            System.err.println("Error: no input received.");
            scanner.close();
            return;
        }

        String input = scanner.nextLine().trim();
        scanner.close();

        int index;
        try {
            /* Integer.parseInt rejects non-numeric input and overflow values */
            index = Integer.parseInt(input);
        } catch (NumberFormatException e) {
            System.err.println("Error: \"" + input + "\" is not a valid integer.");
            return;
        }

        if (index < 0 || index >= VEHICLES.length) {
            System.err.println("Error: index " + index
                    + " is out of bounds (valid range: 0–" + (VEHICLES.length - 1) + ").");
            return;
        }

        System.out.println("Vehicle at index " + index + ": " + VEHICLES[index]);
    }
}
