DST_CAPACITY = 256

def copy_message(dst, src):
    if dst is None or src is None:
        return False
    
    if not isinstance(src, str):
        return False

    # Convert string to bytes
    src_bytes = src.encode('utf-8')
    length = len(src_bytes)

    # Check if it fits in capacity
    if length > DST_CAPACITY:
        return False
    
    # Ensure dst is large enough to be the buffer
    if len(dst) < DST_CAPACITY:
        return False

    try:
        # Copy bytes
        dst[:length] = src_bytes
        # Optional: null terminate if space allows, to mimic C behavior requested
        if length < len(dst):
            dst[length] = 0
        return True
    except Exception:
        return False

if __name__ == "__main__":
    buffer = bytearray(DST_CAPACITY)
    msg = "Hello World"

    if copy_message(buffer, msg):
        print(f"Success: {buffer[:len(msg)].decode()}")
    else:
        print("Failure")
