// Task p4: Prompt user for vehicle index and print vehicle
import java.util.Scanner;

public class P4 {
    public static void main(String[] args) {
        String[] vehicles = {"car", "truck", "motorcycle", "bicycle", "scooter"};
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter index of vehicle: ");
        String input = sc.nextLine();
        try {
            int i = Integer.parseInt(input.trim());
            if (i >= 0 && i < vehicles.length) {
                System.out.println("Selected vehicle: " + vehicles[i]);
            } else {
                System.out.println("Index out of range");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input; please enter an integer");
        }
        sc.close();
    }
}
