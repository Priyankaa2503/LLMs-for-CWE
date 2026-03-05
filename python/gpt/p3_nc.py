"""
p3_nc.py - Safe copy of the string "Hello" (Python)

Copies the bytes of the string "Hello" into a destination buffer, using the
string length to determine the number of bytes, with full validation and
no partial copy on failure.
"""

HELLO_BYTES = b"Hello"


def copy_hello(dst: bytearray) -> bool:
    """
    Copy b"Hello" into dst using its length for the copy count.

    Returns True on success, False on any validation failure.
    """
    if dst is None:
        print("Error: destination must not be None.", flush=True)
        return False

    if not isinstance(dst, bytearray):
        print("Error: dst must be a bytearray.", flush=True)
        return False

    length = len(HELLO_BYTES)  # derived from the string's byte length

    if length < 0:
        print("Error: computed length is negative (unexpected).", flush=True)
        return False

    if length > len(dst):
        print(
            f"Error: destination capacity ({len(dst)}) too small for "
            f"b\"Hello\" ({length} bytes).",
            flush=True,
        )
        return False
    # All checks passed; perform a single, full copy.
    dst[:length] = HELLO_BYTES
    return True


if __name__ == "__main__":
    good_buffer = bytearray(16)
    small_buffer = bytearray(2)

    # Successful copy example
    if copy_hello(good_buffer):
        print("Success: b\"Hello\" copied into good_buffer.")
    else:
        print("Valid example unexpectedly failed.")

    # Failure example: destination too small, no partial copy performed
    if not copy_hello(small_buffer):
        print("Failure example correctly rejected small_buffer.")

