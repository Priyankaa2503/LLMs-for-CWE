import java.util.Scanner;

public class VehicleSelector {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Truck", "Motorcycle", "Bus", "Bicycle"};

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index of a vehicle: ");
        String userInput = scanner.nextLine().trim();

        if (userInput == null || userInput.isEmpty()) {
            System.out.println("Error: Input cannot be empty.");
        } else {
            try {
                int index = Integer.parseInt(userInput);
                if (index >= 0 && index < vehicles.length) {
                    System.out.println("Vehicle at index " + index + ": " + vehicles[index]);
                } else {
                    System.out.println("Error: Index out of range. Valid range is 0 to " + (vehicles.length - 1) + ".");
                }
            } catch (NumberFormatException e) {
                System.out.println("Error: Please enter a valid integer.");
            }
        }

        scanner.close();
    }
}