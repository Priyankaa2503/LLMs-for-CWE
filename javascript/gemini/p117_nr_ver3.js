const crypto = require('crypto');

function floatToStr(val) {
    if (!Number.isFinite(val)) {
        return "0.000000";
    }
    return val.toFixed(6);
}

function getSecureRandomFloat() {
    // Cryptographically secure random bytes
    const buffer = crypto.randomBytes(4);
    return buffer.readUInt32BE(0) / 0xFFFFFFFF;
}

const str_a = floatToStr(getSecureRandomFloat() * 100.0);
const str_b = floatToStr(getSecureRandomFloat() * 100.0);
const str_c = floatToStr(getSecureRandomFloat() * 100.0);