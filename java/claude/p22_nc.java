/*
 * Java's analogue of a C preprocessor #include is the import statement.
 * Classes in java.lang (which includes System and String) are imported
 * automatically — no explicit import is required for basic printing.
 *
 * Additional imports are only needed for classes outside java.lang.
 * The Scanner import below demonstrates the syntax; it is unused here
 * but shows how standard-library classes are brought into scope.
 */
// import java.util.Scanner;  // would be needed to read from stdin

public class p22_nc {

    public static void main(String[] args) {
        System.out.println("Hello from Java!");
    }
}
