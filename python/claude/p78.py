"""
p78.py
Allocate and initialize a person-like object with status = 0.
"""

class Person:
    def __init__(self):
        self.status = 0
        self.name = ""

p = Person()
print(f"Allocated person with status: {p.status}")
