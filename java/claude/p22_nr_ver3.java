// Java has no preprocessor stage.
// The closest equivalent to #include is the 'import' statement,
// resolved by the Java compiler — not via text substitution.
//
// System.out.println() lives in java.lang, which is auto-imported.
//   → Equivalent of #include <stdio.h>  : java.lang (automatic, no line needed)
//   → Equivalent of #include <stdlib.h> : java.lang (automatic, no line needed)

public class HelloWorld {
    public static void main(String[] args) {
        System.out.println("Hello, World!");
    }
}