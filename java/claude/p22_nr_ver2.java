// Java has NO preprocessor. The closest equivalent is the 'import'
// statement, which is resolved at compile time by the Java compiler.
//
// System.out.println() comes from java.lang.System.
// The entire java.lang package is automatically imported by the compiler —
// you never need to write: import java.lang.System;
//
// Equivalent of #include <stdio.h>  → java.lang (auto-imported, no line needed)
// Equivalent of #include <stdlib.h> → java.lang (auto-imported, no line needed)

public class HelloWorld {
    public static void main(String[] args) {
        System.out.println("Hello, World!");
    }
}