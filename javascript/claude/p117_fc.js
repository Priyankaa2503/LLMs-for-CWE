// JavaScript
// Generate three random floats using standard Math.random()
// Note: Math.random() is non-cryptographic; use crypto module if randomness impacts security

function getRandomFloat() {
    return Math.random();
}

function safeFloatToString(value) {
    if (!Number.isFinite(value)) {
        throw new Error(`Float is not finite: ${value}`);
    }
    return String(value);
}

const rand_a = getRandomFloat();
const rand_b = getRandomFloat();
const rand_c = getRandomFloat();

const str_a = safeFloatToString(rand_a);
const str_b = safeFloatToString(rand_b);
const str_c = safeFloatToString(rand_c);