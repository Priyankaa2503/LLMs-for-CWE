def copy_hello(dest, source, dest_capacity):
    """
    Copies source (expected "Hello") to dest.
    """
    # First check that destination and source are valid
    if dest is None or source is None:
        return False # Fail

    # Compute n = length("Hello")
    encoded_source = source.encode('utf-8')
    n = len(encoded_source)

    # Verify that n does not exceed the destination capacity
    if (n > dest_capacity):
        return False # Fail
    
    if (n > len(dest)):
        return False # Fail

    # Otherwise copy exactly n bytes and report success
    try:
        for i in range(n):
            dest[i] = encoded_source[i]
        return True # Success
    except Exception:
        return False
