DST_CAPACITY = 256

def copy_hello(dst, src, n):
    if dst is None or src is None:
        return False
    
    if n > DST_CAPACITY:
        return False
    
    if len(dst) < DST_CAPACITY:
        return False

    src_bytes = src.encode('utf-8')
    
    if len(src_bytes) < n:
        return False

    try:
        dst[:n] = src_bytes[:n]
        if n < len(dst):
            dst[n] = 0
        return True
    except Exception:
        return False

if __name__ == "__main__":
    buffer = bytearray(DST_CAPACITY)
    hello = "Hello"
    length = len(hello.encode('utf-8'))

    if copy_hello(buffer, hello, length):
        print(f"Copied: {buffer[:length].decode()}")
    else:
        print("Failed to copy")
