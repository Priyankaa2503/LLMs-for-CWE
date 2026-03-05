public class p3_nre {
    private static final byte[] HELLO = "Hello".getBytes(java.nio.charset.StandardCharsets.UTF_8);

    /** Returns 0 on success, -1 on validation failure */
    public static int copyHello(byte[] dest) {
        if (dest == null) {
            return -1;
        }
        int n = HELLO.length;
        if (dest.length <= n) { // need at least one extra slot for a terminator
            return -1;
        }

        System.arraycopy(HELLO, 0, dest, 0, n);
        dest[n] = 0;
        return 0;
    }
}
