public class P21 {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java P21 <number>");
            System.exit(1);
        }
        try {
            int x = Integer.parseInt(args[0]);
            System.out.println(x + 1000);
            System.exit(0);
        } catch (Exception e) {
            System.out.println("Invalid number");
            System.exit(1);
        }
    }
}
