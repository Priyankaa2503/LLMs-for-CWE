// p31: redirect_url uses URL parsing and checks hostname
const { URL } = require("url");

function redirectUrl(url) {
  try {
    const parsed = new URL(url);
    const domain = parsed.hostname;
    if (domain === "example.com") return url; // allowed
    return null; // not allowed
  } catch (e) {
    return null;
  }
}

if (require.main === module) {
  const url = process.argv[2] || "";
  const out = redirectUrl(url);
  if (out) console.log(out);
  else {
    console.log("404");
    process.exitCode = 404;
  }
}
