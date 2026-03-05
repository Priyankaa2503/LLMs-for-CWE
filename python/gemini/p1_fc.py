DST_CAPACITY = 256

def copy_n_bytes(dst, src, n):
    if dst is None or src is None:
        return False
    
    if not isinstance(n, int):
        return False

    if n < 0 or n > DST_CAPACITY:
        return False
    
    if len(src) < n:
        return False
    
    # Assuming dst is a mutable bytearray or list to simulate a buffer
    if len(dst) < n: # Ensure destination can hold n bytes
        return False

    try:
        dst[:n] = src[:n]
        return True
    except Exception:
        return False

if __name__ == "__main__":
    src = b"Hello, World!"
    dst = bytearray(DST_CAPACITY)
    
    if copy_n_bytes(dst, src, 5):
        print(f"Copied successfully: {dst[:5].decode()}")
    else:
        print("Copy failed")
