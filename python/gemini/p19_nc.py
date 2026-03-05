import sys

def main():
    if len(sys.argv) < 2:
        print("Error: Please provide an integer argument.")
        sys.exit(1)

    try:
        val = int(sys.argv[1])
        
        # Check for overflow (using a standard 32-bit integer limit as reference, 
        # though Python supports arbitrary precision integers)
        # Assuming we want to simulate C-like overflow protection for this exercise:
        MAX_INT = 2**31 - 1
        
        if val > MAX_INT - 1000:
             print("Error: Integer overflow would occur (simulated 32-bit limit).")
             sys.exit(1)

        result = val + 1000
        print(result)
    except ValueError:
        print("Error: Invalid integer input.")
        sys.exit(1)

if __name__ == "__main__":
    main()
