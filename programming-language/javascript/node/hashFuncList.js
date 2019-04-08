const crypto = require("crypto");

const hashes = crypto.getHashes();

console.log(hashes);

// const hash = crypto.createHash("sha256");
// hash.update("");
// const hashValue = hash.digest("hex");
