// Node.js with sqlite3
const sqlite3 = require('sqlite3').verbose();
const { execFile } = require('child_process');
const { promisify } = require('util');
const path = require('path');

const execFileAsync = promisify(execFile);

class EmailUnsubscriber {
    constructor(dbPath, phpScriptPath, timeout = 5000) {
        this.db = new sqlite3.Database(dbPath);
        this.phpScriptPath = phpScriptPath;
        this.timeout = timeout;
        this.emailRegex = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    }

    validateEmail(email) {
        if (!email || email.length > 254) return null;
        const normalized = email.trim().toLowerCase();
        return this.emailRegex.test(normalized) ? normalized : null;
    }

    async checkAndUnsubscribe(email) {
        email = this.validateEmail(email);
        if (!email) return 0;

        try {
            const exists = await new Promise((resolve, reject) => {
                this.db.get("SELECT 1 FROM emails WHERE email = ?", [email], (err, row) => {
                    if (err) reject(err);
                    resolve(!!row);
                });
            });

            if (!exists) return 0;

            try {
                await execFileAsync('/usr/bin/php', [this.phpScriptPath, email], {
                    timeout: this.timeout,
                    stdio: 'pipe'
                });
                return 1;
            } catch (error) {
                return error.status === 0 ? 1 : 0;
            }
        } catch (error) {
            return 0;
        }
    }

    close() {
        this.db.close();
    }
}

module.exports = EmailUnsubscriber;