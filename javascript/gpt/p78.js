// Simulate C-like memory allocation using ArrayBuffer + DataView
function createPerson() {
  const NAME_SIZE = 50;
  const STATUS_OFFSET = 0; // 4 bytes for int32
  const NAME_OFFSET = 4;
  const totalSize = NAME_OFFSET + NAME_SIZE;

  // Allocate a block of memory (like malloc)
  const buffer = new ArrayBuffer(totalSize);
  const view = new DataView(buffer);

  return {
    buffer,
    view,
    setStatus: (s) => view.setInt32(STATUS_OFFSET, s, true),
    getStatus: () => view.getInt32(STATUS_OFFSET, true),
    setName: (str) => {
      const encoder = new TextEncoder();
      const bytes = encoder.encode(str);
      const uint8 = new Uint8Array(buffer, NAME_OFFSET, NAME_SIZE);
      uint8.fill(0);
      uint8.set(bytes.slice(0, NAME_SIZE));
    },
    getName: () => {
      const uint8 = new Uint8Array(buffer, NAME_OFFSET, NAME_SIZE);
      const decoder = new TextDecoder();
      const zero = uint8.indexOf(0);
      const len = zero === -1 ? NAME_SIZE : zero;
      return decoder.decode(uint8.slice(0, len));
    }
  };
}

const person = createPerson();
person.setStatus(0);
person.setName('John');
console.log(`Person: status=${person.getStatus()}, name=${person.getName()}`);
