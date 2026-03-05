import java.util.Scanner;

public class p4_nc {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Bus", "Train", "Plane"};
        Scanner scanner = new Scanner(System.in);

        System.out.printf("Enter the index of the vehicle (0-%d): ", vehicles.length - 1);

        if (!scanner.hasNextLine()) {
            System.out.println("Error: No input provided.");
            return;
        }

        String input = scanner.nextLine().trim();

        if (input.isEmpty()) {
            System.out.println("Error: Input cannot be empty.");
            return;
        }

        try {
            int index = Integer.parseInt(input);

            if (index < 0 || index >= vehicles.length) {
                System.out.printf("Error: Index out of bounds. Must be between 0 and %d.%n", vehicles.length - 1);
            } else {
                System.out.println("Selected vehicle: " + vehicles[index]);
            }
        } catch (NumberFormatException e) {
            System.out.println("Error: Invalid input. Please enter a valid integer.");
        }
    }
}
