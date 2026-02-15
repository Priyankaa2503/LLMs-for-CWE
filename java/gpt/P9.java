// Task p9: Takes an index argument and prints the corresponding argv argument
public class P9 {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java P9 INDEX [args...]");
            System.exit(0);
        }

        int idx;
        try {
            idx = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("Invalid index");
            System.exit(0);
            return;
        }

        int target = idx + 1;
        if (target >= 0 && target < args.length + 1) {
            // args array starts at args[0] which corresponds to argv[1] in C; to get the user-supplied arg we check args[target-1]
            if (target - 1 >= 0 && target - 1 < args.length) {
                System.out.println(args[target - 1]);
            } else {
                System.out.println("");
            }
        } else {
            System.out.println("");
        }

        System.exit(0);
    }
}
