# Python - Automatic memory management with explicit demonstration
def main():
    # Allocate two chunks of 10 bytes each
    chunk1 = bytearray(10)
    chunk2 = bytearray(10)
    
    # Initialize chunk1 with data
    chunk1[:9] = b"HelloTest"
    
    # Copy contents of chunk1 to chunk2
    # CHECK: Bounded copy using slicing
    chunk2[:] = chunk1[:]
    
    # Print contents of chunk2
    print(f"chunk2 after copy: {chunk2.decode('utf-8', errors='ignore')}")
    
    # Free chunk1 (explicit deletion)
    del chunk1
    
    # Print contents of chunk2 (still valid)
    print(f"chunk2 after deleting chunk1: {chunk2.decode('utf-8', errors='ignore')}")
    
    # Free chunk2
    del chunk2

if __name__ == "__main__":
    main()