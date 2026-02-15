# Task p8: Demonstrate argc and argv behavior
import sys


def main():
    argc = len(sys.argv)
    print(f"argc = {argc}")
    for i, arg in enumerate(sys.argv):
        print(f"argv[{i}] = {arg}")
    # Example note printed for clarity
    print(
        "Note: argv[0] is the program name. If you ran './a.out foo bar baz', argc would be 4."
    )
    return 0


if __name__ == "__main__":
    sys.exit(main())
