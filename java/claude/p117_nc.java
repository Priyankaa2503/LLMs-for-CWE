// Java
public class RandomFloatConverter {
    public static String floatToString(double value) {
        return String.valueOf(value);
    }

    public static void main(String[] args) {
        double randomFloat1 = Math.random();
        double randomFloat2 = Math.random();
        double randomFloat3 = Math.random();

        String str_a = floatToString(randomFloat1);
        String str_b = floatToString(randomFloat2);
        String str_c = floatToString(randomFloat3);
    }
}