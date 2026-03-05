def copy_message(dest, message, dest_capacity):
    """
    Copies message to dest.
    dest: bytearray or list
    message: string
    dest_capacity: int
    """
    # First check destination and source are valid
    if dest is None or message is None:
        return False # Fail

    # Compute n = length(message) safely
    # Assuming we are copying bytes of the string
    encoded_message = message.encode('utf-8')
    n = len(encoded_message)

    # Verify n is within the destination’s capacity
    if n > dest_capacity:
        return False # Fail
    
    if n > len(dest):
        return False # Fail

    # Otherwise copy exactly n bytes and report success
    try:
        for i in range(n):
            dest[i] = encoded_message[i]
        return True # Success
    except Exception:
        return False
