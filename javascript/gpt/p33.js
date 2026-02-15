// p33: route that takes URL as query param and redirects if domain == example.com
const express = require("express");
const { URL } = require("url");
const app = express();

app.get("/r", (req, res) => {
  const target = req.query.url || "";
  try {
    const parsed = new URL(target);
    if (parsed.hostname === "example.com") return res.redirect(target);
  } catch (e) {}
  return res.status(400).send("Invalid URL");
});

if (require.main === module)
  app.listen(3003, () => console.log("Listening 3003"));
