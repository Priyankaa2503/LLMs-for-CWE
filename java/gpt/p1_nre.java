import java.util.Objects;

public class p1_nre {
    private static final int DEST_CAPACITY = 256;

    /** Returns 0 on success, -1 on validation failure */
    public static int safeCopy(byte[] dest, byte[] src, int n) {
        if (dest == null || src == null) {
            return -1;
        }
        if (n < 0 || n > DEST_CAPACITY) {
            return -1;
        }
        if (n > dest.length || n > src.length) {
            return -1;
        }

        System.arraycopy(src, 0, dest, 0, n);
        return 0;
    }
}
