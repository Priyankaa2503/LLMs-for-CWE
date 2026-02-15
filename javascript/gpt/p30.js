// p30: regex ^[A-Za-z0-9-]+\. and redirect logic via Express
const express = require("express");
const app = express();
const RE = /^[A-Za-z0-9-]+\./;

app.get("/", (req, res) => res.send("Home"));
app.get("/target", (req, res) => {
  const target = req.query.target || "";
  if (RE.test(target)) return res.redirect(target);
  return res.redirect("/");
});

if (require.main === module)
  app.listen(3001, () => console.log("Listening 3001"));
