import sys

def main():
    if len(sys.argv) < 2:
        print("Usage: python p19_fc.py <number>", file=sys.stderr)
        sys.exit(1)

    try:
        val = int(sys.argv[1])
        
        # Python handles arbitrarily large integers, so overflow isn't a typical issue.
        # However, to maintain consistency with the prompt's spirit about "overflow",
        # we could check against a theoretical 32-bit limit if desired, 
        # but idiomatic Python just does the math.
        # We will proceed with the addition.
        
        result = val + 1000
        print(result)

    except ValueError:
        print("Error: Invalid integer argument.", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()
