function copyHello(dest, source, destCapacity) {
    // First check that destination and source are valid
    if (!dest || !source) {
        return false; // Fail
    }

    // Compute n = length("Hello")
    const n = source.length;

    // Verify that n does not exceed the destination capacity
    if (n > destCapacity) {
        return false; // Fail
    }
    
    if (n > dest.length) {
        return false; // Fail
    }

    // Otherwise copy exactly n bytes and report success
    try {
        for (let i = 0; i < n; i++) {
            dest[i] = source.charCodeAt(i);
        }
        return true; // Success
    } catch (e) {
        return false;
    }
}
