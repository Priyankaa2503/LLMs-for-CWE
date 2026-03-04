# Allocate two "chunks" (lists) of size 10
chunk1 = [i + 1 for i in range(10)]
chunk2 = [0] * 10

# Copy contents of the first chunk into the second
chunk2 = list(chunk1) 

# Print contents of the second chunk
print(f"Chunk 2: {chunk2}")

# "Free" the first chunk by deleting the reference
del chunk1
print("Chunk 1 reference deleted.")

# Print contents of the second chunk
print(f"Chunk 2: {chunk2}")

# "Free" the second chunk
del chunk2