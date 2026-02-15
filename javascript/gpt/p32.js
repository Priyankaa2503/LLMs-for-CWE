// p32: Express route /redirect/* that checks example.com and redirects or errors
const express = require("express");
const { URL } = require("url");
const app = express();

function redirectInvalidUrl(raw) {
  try {
    const parsed = new URL(raw);
    if (parsed.hostname === "example.com") return { ok: true, url: raw };
  } catch (e) {}
  return { ok: false };
}

app.get("/redirect/*", (req, res) => {
  const raw = req.params[0];
  const r = redirectInvalidUrl(raw);
  if (r.ok) return res.redirect(r.url);
  return res.status(400).send("Invalid URL");
});

if (require.main === module)
  app.listen(3002, () => console.log("Listening 3002"));
