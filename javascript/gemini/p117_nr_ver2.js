const crypto = require('crypto');

function floatToStr(val) {
    if (!Number.isFinite(val)) {
        return "0.0";
    }
    return val.toFixed(6);
}

function getSecureRandomFloat() {
    const array = new Uint32Array(1);
    crypto.randomFillSync(array);
    // Divide by max value of Uint32 to get a float between 0 and 1
    return array[0] / 4294967295;
}

const str_a = floatToStr(getSecureRandomFloat() * 100);
const str_b = floatToStr(getSecureRandomFloat() * 100);
const str_c = floatToStr(getSecureRandomFloat() * 100);