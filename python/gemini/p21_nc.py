import sys

def main():
    if len(sys.argv) < 2:
        sys.exit(1)

    try:
        val = int(sys.argv[1])
        
        # Check for overflow (using a standard 32-bit integer limit as reference)
        MAX_INT = 2**31 - 1
        
        if val > MAX_INT - 1000:
             sys.exit(1)

        result = val + 1000
        print(result)
        sys.exit(0)
    except ValueError:
        sys.exit(1)

if __name__ == "__main__":
    main()
