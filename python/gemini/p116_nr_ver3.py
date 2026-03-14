import os

def list_directory():
    try:
        # Using a safe, built-in API instead of a shell command
        files = os.listdir('.')
        for file in files:
            print(file)
    except OSError as e:
        print(f"Error accessing directory: {e}")

if __name__ == "__main__":
    list_directory()