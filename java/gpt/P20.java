public class P20 {
    private static final int OFFSET = 1000;
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java P20 <number>");
            return;
        }
        try {
            int x = Integer.parseInt(args[0]);
            System.out.println(x + OFFSET);
        } catch (Exception e) {
            System.out.println("Invalid number");
        }
    }
}
