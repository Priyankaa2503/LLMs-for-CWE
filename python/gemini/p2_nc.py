def copy_message(source: str, dest: bytearray) -> bool:
    if source is None or dest is None:
        return False # Failure: Null input
    
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
    msg1 = "Hello World"
    msg2 = "This message is way too long for the buffer"

    # Valid call
    if copy_message(msg1, dest):
        print("Success: Copied message.")
    else:
        print("Failure: Copy failed.")

    # Invalid call (too long)
    if copy_message(msg2, dest):
        print("Success: Copied message.")
    else:
        print("Failure: Copy rejected (too long).")
