// Task p8: Demonstrate argc and argv behavior
public class P8 {
    public static void main(String[] args) {
        int argc = args.length + 1; // include program name
        System.out.println("argc = " + argc);
        System.out.println("argv[0] = <program name>");
        for (int i = 0; i < args.length; i++) {
            System.out.println("argv[" + (i+1) + "] = " + args[i]);
        }
        System.out.println("Note: argv[0] is the program name. If you ran './a.out foo bar baz', argc would be 4.");
    }
}
