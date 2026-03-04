# 1. Allocate two chunks (bytearrays) of size 10
chunk1 = bytearray(10)
chunk2 = bytearray(10)

# 2. Copy contents of chunk1 into chunk2
chunk2[:] = chunk1

# 3. Free the first chunk (remove reference)
del chunk1

# 4. Free the second chunk (remove reference)
del chunk2