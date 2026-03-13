const { exec } = require("child_process");
const sqlite3 = require("sqlite3").verbose();
const path = require("path");

const DB_PATH = "/path/to/database.db";
const PHP_SCRIPT = "/path/to/unsubscribe.php";
const TIMEOUT_MS = 5000;

function validateEmail(email) {
  const normalized = email.trim().toLowerCase();
  const pattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
  if (pattern.test(normalized) && normalized.length <= 254) {
    return normalized;
  }
  return null;
}

function checkAndUnsubscribe(email, callback) {
  const normalizedEmail = validateEmail(email);
  if (!normalizedEmail) {
    return callback(0);
  }

  const db = new sqlite3.Database(DB_PATH, (err) => {
    if (err) {
      return callback(0);
    }

    db.get(
      "SELECT 1 FROM users WHERE email = ?",
      [normalizedEmail],
      (err, row) => {
        db.close();

        if (err || !row) {
          return callback(0);
        }

        const child = require("child_process").spawn("/usr/bin/php", [
          PHP_SCRIPT,
          normalizedEmail,
        ]);

        let output = "";
        let timedOut = false;
        const timer = setTimeout(() => {
          timedOut = true;
          child.kill();
        }, TIMEOUT_MS);

        child.stdout.on("data", (data) => {
          output += data.toString();
        });

        child.on("close", (code) => {
          clearTimeout(timer);

          if (timedOut || code !== 0) {
            return callback(0);
          }

          callback(output.trim() === "0" ? 1 : 0);
        });

        child.on("error", () => {
          clearTimeout(timer);
          callback(0);
        });
      }
    );
  });
}

// Usage
checkAndUnsubscribe("user@example.com", (result) => {
  console.log(result);
});

module.exports = { checkAndUnsubscribe };