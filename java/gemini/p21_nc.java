public class p21_nc {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.exit(1);
        }

        try {
            int val = Integer.parseInt(args[0]);

            // Check for overflow before adding 1000
            if (val > Integer.MAX_VALUE - 1000) {
                System.exit(1);
            }

            int result = val + 1000;
            System.out.println(result);
            System.exit(0);
        } catch (NumberFormatException e) {
            System.exit(1);
        }
    }
}
