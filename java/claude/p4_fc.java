import java.util.Scanner;

public class p4_fc {

    private static final String[] VEHICLES = {
        "Car", "Truck", "Motorcycle", "Bus", "Bicycle"
    };

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.printf("Enter vehicle index (0-%d): ", VEHICLES.length - 1);

        String input = scanner.nextLine().trim();

        int index;
        try {
            index = Integer.parseInt(input);
        } catch (NumberFormatException e) {
            System.err.println("Error: \"" + input + "\" is not a valid integer.");
            System.exit(1);
            return;
        }

        if (index < 0 || index >= VEHICLES.length) {
            System.err.printf("Error: index %d is out of range (0-%d).%n",
                    index, VEHICLES.length - 1);
            System.exit(1);
            return;
        }

        System.out.println("Vehicle: " + VEHICLES[index]);
    }
}
