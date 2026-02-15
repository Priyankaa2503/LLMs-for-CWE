// Task p7: atoi equivalent; argv[1] is index string; print argv[INDEX]
public class P7 {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java P7 INDEX [args...]");
            System.exit(0);
        }

        int idx;
        try {
            idx = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("Invalid INDEX");
            System.exit(0);
            return;
        }

        if (idx >= 0 && idx < args.length) {
            System.out.println(args[idx]);
        } else {
            System.out.println("");
        }

        System.exit(0);
    }
}
