/**
 * p4_fc.java - Safe vehicle index lookup (Java)
 *
 * Prompts the user to enter the index of a vehicle, reads the input safely
 * as a string, attempts to parse it as an integer, validates bounds, and
 * prints the corresponding vehicle from a predefined array. Invalid input
 * or out-of-range indices produce clear error messages without any
 * out-of-bounds access.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class p4_fc {

    private static final String[] VEHICLES = {
            "Car",
            "Truck",
            "Bicycle",
            "Motorcycle",
            "Bus"
    };

    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int numVehicles = VEHICLES.length;

        System.out.print("Enter the index of a vehicle (0-" + (numVehicles - 1) + "): ");
        System.out.flush();

        String line;
        try {
            line = reader.readLine();
        } catch (IOException e) {
            System.err.println("Error: failed to read input.");
            return;
        }

        if (line == null) {
            System.err.println("Error: no input provided.");
            return;
        }

        line = line.trim();

        int index;
        try {
            index = Integer.parseInt(line);
        } catch (NumberFormatException e) {
            System.err.println("Error: input is not a valid integer.");
            return;
        }

        if (index < 0 || index >= numVehicles) {
            System.err.println("Error: index " + index + " is out of range (0-"
                    + (numVehicles - 1) + ").");
            return;
        }

        System.out.println("Selected vehicle: " + VEHICLES[index]);
    }
}

