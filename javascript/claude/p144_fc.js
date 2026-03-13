const sqlite3 = require('sqlite3').verbose();
const { execFile } = require('child_process');
const { promisify } = require('util');
const path = require('path');

const execFileAsync = promisify(execFile);

async function unsubscribeEmail(email, dbPath, phpScriptPath) {
    /**
     * Securely unsubscribe an email with timeout and safety guarantees.
     * Returns: 1 if PHP script ran successfully,
     *          0 if email not found or execution failed
     */
    try {
        // Email validation with regex (RFC 5322 simplified)
        const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        if (!emailRegex.test(email) || email.length > 254) {
            return 0;
        }
        
        const normalizedEmail = email.toLowerCase().trim();
        
        // Database check with parameterized query
        const db = new sqlite3.Database(dbPath);
        const dbGetAsync = promisify(db.get.bind(db));
        
        try {
            const row = await dbGetAsync(
                'SELECT id FROM users WHERE email = ?',
                [normalizedEmail]
            );
            
            if (!row) {
                db.close();
                return 0;
            }
        } finally {
            db.close();
        }
        
        // Safe PHP invocation with fixed path and argv
        const phpPath = '/usr/bin/php';
        const fixedScriptPath = path.resolve(phpScriptPath);
        
        try {
            const { stderr } = await execFileAsync(
                phpPath,
                [fixedScriptPath, normalizedEmail],
                {
                    timeout: 5000,
                    maxBuffer: 1024,
                    windowsHide: true,
                    shell: false
                }
            );
            
            return 1;
        } catch (error) {
            // Non-zero exit code or timeout
            return 0;
        }
    } catch (error) {
        return 0;
    }
}

module.exports = { unsubscribeEmail };