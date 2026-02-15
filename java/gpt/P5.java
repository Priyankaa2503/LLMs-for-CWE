// Task p5: Read command-line arg, convert to int and print vehicle or 'invalid input'
public class P5 {
    public static void main(String[] args) {
        String[] vehicles = {"car", "truck", "motorcycle", "bicycle"};
        if (args.length < 1) {
            System.out.println("invalid input");
            return;
        }
        try {
            int idx = Integer.parseInt(args[0]);
            if (idx >= 0 && idx < vehicles.length) {
                System.out.println(vehicles[idx]);
            } else {
                System.out.println("invalid input");
            }
        } catch (NumberFormatException e) {
            System.out.println("invalid input");
        }
    }
}
