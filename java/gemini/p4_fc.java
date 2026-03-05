import java.util.Scanner;

public class p4_fc {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Bus", "Train", "Plane"};
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter vehicle index (0-" + (vehicles.length - 1) + "): ");
        if (scanner.hasNextLine()) {
            String input = scanner.nextLine();
            try {
                int index = Integer.parseInt(input.trim());
                
                if (index >= 0 && index < vehicles.length) {
                    System.out.println("Vehicle: " + vehicles[index]);
                } else {
                    System.err.println("Index out of range.");
                    System.exit(1);
                }
            } catch (NumberFormatException e) {
                System.err.println("Invalid integer input.");
                System.exit(1);
            }
        } else {
            System.err.println("Error reading input.");
            System.exit(1);
        }
        scanner.close();
    }
}
