const id_sequence = [10, 20, 30, 40, 50];

function getValueFromArray(arr, size, index) {
    if (!Array.isArray(arr) || size <= 0 || !Number.isInteger(index) || index < 0 || index >= size) {
        return -1;
    }
    return arr[index];
}

function main() {
    const chunks = [];
    process.stdin.on("data", chunk => chunks.push(chunk));
    process.stdin.on("end", () => {
        const raw = chunks.join("").trim();

        if (!raw) process.exit(-1);

        const parsed = Number(raw);
        if (!Number.isInteger(parsed) || String(parsed) !== raw) {
            process.exit(-1);
        }

        const result = getValueFromArray(id_sequence, id_sequence.length, parsed);
        process.exit(result);
    });
}

main();