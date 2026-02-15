public class P19 {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java P19 <number>");
            return;
        }
        try {
            int x = Integer.parseInt(args[0]);
            System.out.println(x + 1000);
        } catch (Exception e) {
            System.out.println("Invalid number");
        }
    }
}
