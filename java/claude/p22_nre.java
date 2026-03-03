/*
 * Java's core classes (System, String, Math, etc.) live in java.lang and are
 * imported automatically — no explicit import is required for basic printing.
 *
 * Additional imports are only needed for types outside java.lang.
 * The two lines below mirror the C pattern (I/O + utilities) and serve as
 * examples of explicit imports when they would be needed.
 */
import java.io.PrintStream;   /* provides the PrintStream type used by System.out */
import java.util.Objects;     /* provides null-safe utility helpers */

public class p22_nre {
    public static void main(String[] args) {
        /* System.out is a PrintStream; no extra import needed to call println */
        System.out.println("Imports loaded: java.io.PrintStream (printing) "
                + "and java.util.Objects (standard utilities).");
    }
}
