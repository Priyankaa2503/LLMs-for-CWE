# Python
import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

ctypes.memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), 10)
ctypes.memmove(ctypes.addressof(chunk1), b"Hello", 5)
ctypes.memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), 10)

print("Chunk2 contents:", chunk2.value)

chunk1 = None

print("Chunk2 after deleting chunk1:", chunk2.value)

chunk2 = None