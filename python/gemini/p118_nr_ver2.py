import secrets
import os

def write_random_data():
    base_dir = "/tmp/secure_storage"
    file_path = os.path.join(base_dir, "output.txt")
    
    # Secure RNG for floats
    random_floats = [str(secrets.SystemRandom().random()) for _ in range(3)]
    content = "".join(random_floats)
    
    try:
        if not os.path.exists(base_dir):
            os.makedirs(base_dir, mode=0o700)
            
        with open(file_path, "w", encoding="utf-8") as f:
            f.write(content)
            
    except (IOError, OSError):
        pass

if __name__ == "__main__":
    write_random_data()