"""
p2_nc.py - Safe message-to-buffer copy using string length (Python)

Copies bytes from a source message into a destination buffer, using the
message's byte length as the number of bytes to copy.
"""

from typing import Union

DEST_CAPACITY = 256


def copy_message_to_buffer(
    msg: Union[str, bytes, bytearray],
    dst: bytearray,
) -> bool:
    """
    Copy bytes from msg into dst using the message's encoded byte length.

    Returns True on success, False on any validation failure.
    """
    if dst is None or msg is None:
        print("Error: destination and message must not be None.", flush=True)
        return False

    if not isinstance(dst, bytearray):
        print("Error: dst must be a bytearray.", flush=True)
        return False

    if len(dst) <= 0:
        print("Error: destination capacity must be positive.", flush=True)
        return False

    if isinstance(msg, str):
        msg_bytes = msg.encode("utf-8")
    elif isinstance(msg, (bytes, bytearray)):
        msg_bytes = bytes(msg)
    else:
        print("Error: msg must be a str, bytes, or bytearray.", flush=True)
        return False

    copy_len = len(msg_bytes)  # derived from string/bytes length

    if copy_len < 0:
        print("Error: computed length is negative (unexpected).", flush=True)
        return False

    if copy_len > DEST_CAPACITY or copy_len > len(dst):
        print(
            f"Error: copy length ({copy_len}) exceeds destination capacity "
            f"({min(DEST_CAPACITY, len(dst))}).",
            flush=True,
        )
        return False

    dst[:copy_len] = msg_bytes[:copy_len]
    return True


if __name__ == "__main__":
    dst = bytearray(DEST_CAPACITY)

    # Successful copy example
    if copy_message_to_buffer("Hello, secure world!", dst):
        print("Success: copied message bytes.")
    else:
        print("Valid example unexpectedly failed.")

    # Failure example: destination too small for message
    small_dst = bytearray(8)
    if not copy_message_to_buffer("This message is too long for 8 bytes", small_dst):
        print("Failure example correctly rejected oversize copy.")

