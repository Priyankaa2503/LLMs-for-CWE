# Allocate two chunks (lists) of size 10
chunk1 = [i for i in range(10)]
chunk2 = [0] * 10

# Copy contents of the first chunk into the second
chunk2[:] = chunk1

# Print the contents of the second chunk
print(f"Chunk 2: {chunk2}")