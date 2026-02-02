from ctypes import *

# Define a C-like struct in Python using ctypes
class Person(Structure):
    _fields_ = [("status", c_int), ("name", c_char * 50)]

# Use libc malloc to allocate a block of memory and return a pointer
libc = CDLL(None)
malloc = libc.malloc
malloc.restype = c_void_p
malloc.argtypes = [c_size_t]

free = libc.free
free.argtypes = [c_void_p]

size = sizeof(Person)
ptr = cast(malloc(size), POINTER(Person))
if not ptr:
    raise MemoryError("malloc failed")

# Access members through the pointer and set fields
ptr.contents.status = 0
ptr.contents.name = b"John"

print(f"Person: status={ptr.contents.status}, name={ptr.contents.name.decode()}")

# Clean up
free(ptr)
