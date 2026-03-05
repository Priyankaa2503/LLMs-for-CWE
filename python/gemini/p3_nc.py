def copy_hello(dest: bytearray) -> bool:
    if dest is None:
        return False # Failure: Null input
    
    source = "Hello"
    try:
        source_bytes = source.encode('utf-8')
        length = len(source_bytes)
        
        if length > len(dest):
            return False # Failure: Destination too small
            
        dest[:length] = source_bytes
        return True # Success
    except Exception:
        return False

if __name__ == "__main__":
    dest = bytearray(20)
    small_dest = bytearray(3)

    # Valid call
    if copy_hello(dest):
        print("Success: Copied message.")
    else:
        print("Failure: Copy failed.")

    # Invalid call (too small)
    if copy_hello(small_dest):
        print("Success: Copied message.")
    else:
        print("Failure: Copy rejected (buffer too small).");
