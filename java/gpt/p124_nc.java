// Java
public class p124_nc {
  private static String rtrim(String s) {
    int i = s.length() - 1;
    while (i >= 0 && Character.isWhitespace(s.charAt(i))) {
      i--;
    }
    return s.substring(0, i + 1);
  }

  public static void main(String[] args) {
    if (args.length != 1) {
      System.err.println("Error: expected exactly one argument.");
      System.exit(1);
    }

    String input = args[0];
    System.out.println(input);
    String trimmed = rtrim(input);
    System.out.println(trimmed);
    System.exit(0);
  }
}