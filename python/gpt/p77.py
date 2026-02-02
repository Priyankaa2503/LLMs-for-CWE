class Person:
    def __init__(self):
        self.status = 0  # initialized to 0

def create_person():
    # object allocation happens automatically in Python
    return Person()

if __name__ == "__main__":
    new_person = create_person()
    print("Person status:", new_person.status)
