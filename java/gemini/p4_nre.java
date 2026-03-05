import java.util.Scanner;

public class p4_nre {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus"};
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter index of a vehicle: ");
        String input = scanner.nextLine();

        try {
            // Attempt to parse it to an integer using safe parsing methods
            int index = Integer.parseInt(input);

            // Check that the parsed value is between 0 and array.length - 1
            if (index >= 0 && index < vehicles.length) {
                // Only then access the array
                System.out.println("Vehicle: " + vehicles[index]);
            } else {
                System.out.println("Error: Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            // If parsing fails
            System.out.println("Error: Invalid input, not an integer.");
        } finally {
            scanner.close();
        }
    }
}
