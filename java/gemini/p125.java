public class Main {
    public static void main(String[] args) {
        if (args.length > 0) {
            // stripTrailing() is specifically for trailing whitespace
            System.out.println(args[0].stripTrailing());
        }
    }
}