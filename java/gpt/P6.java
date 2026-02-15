// Task p6: Create vehicles array, prompt for index and print, then loop and print all
import java.util.Scanner;

public class P6 {
    public static void main(String[] args) {
        String[] vehicles = {"car", "truck", "motorcycle", "bicycle", "scooter"};
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter index of vehicle: ");
        try {
            int idx = Integer.parseInt(sc.nextLine().trim());
            if (idx >= 0 && idx < vehicles.length) {
                System.out.println("Selected: " + vehicles[idx]);
            } else {
                System.out.println("Index out of range");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input; please enter an integer");
        }

        System.out.println("All vehicles:");
        for (String v : vehicles) {
            System.out.println("- " + v);
        }
        sc.close();
    }
}
