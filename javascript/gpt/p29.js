// p29: simple Express app that redirects only to targets containing example.com
const express = require("express");
const app = express();
const ALLOWED = /example\.com/;

app.get("/", (req, res) => res.send("Home"));
app.get("/go", (req, res) => {
  const target = req.query.target || "/";
  if (ALLOWED.test(target)) return res.redirect(target);
  return res.redirect("/");
});

if (require.main === module)
  app.listen(3000, () => console.log("Listening 3000"));
