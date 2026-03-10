// JavaScript (Node.js-style streams)
import { StringDecoder } from "string_decoder";
import { URLSearchParams } from "url";

const MAX_REQ_BYTES = 8192;
const MAX_USER_LEN = 32;
const USERNAME_RE = /^[A-Za-z0-9_-]{1,32}$/;

function htmlEscape(s) {
  return String(s)
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;")
    .replace(/"/g, "&quot;")
    .replace(/'/g, "&#39;");
}

function writeResponse(respStream, statusCode, reason, body) {
  const bodyBuf = Buffer.from(body, "utf8");
  const headers =
    `HTTP/1.1 ${statusCode} ${reason}\r\n` +
    `Content-Type: text/html; charset=utf-8\r\n` +
    `X-Content-Type-Options: nosniff\r\n` +
    `Content-Length: ${bodyBuf.length}\r\n` +
    `Connection: close\r\n` +
    `\r\n`;
  respStream.write(headers, "ascii");
  respStream.write(bodyBuf);
  if (typeof respStream.end === "function") respStream.end();
}

function extractUsernameFromRequestText(text) {
  const lines = text.split(/\r?\n/);
  const first = lines[0] || "";
  const parts = first.split(" ");
  if (parts.length >= 2) {
    const path = parts[1];
    const qIndex = path.indexOf("?");
    if (qIndex !== -1) {
      const qs = path.slice(qIndex + 1);
      const params = new URLSearchParams(qs);
      const u = params.get("username");
      if (u) return u;
    }
  }

  // Body parse
  const split = text.includes("\r\n\r\n") ? "\r\n\r\n" : "\n\n";
  const body = text.includes(split) ? text.split(split, 2)[1] : text;
  const params = new URLSearchParams(body);
  const u = params.get("username");
  return u || null;
}

function isValidUsername(u) {
  if (typeof u !== "string") return false;
  if (u.length === 0 || u.length > MAX_USER_LEN) return false;
  return USERNAME_RE.test(u);
}

// requestStream: readable stream containing raw HTTP request bytes
// responseStream: writable stream for raw HTTP response bytes
export async function http_hello_page(requestStream, responseStream) {
  if (!requestStream || !responseStream) return;

  const decoder = new StringDecoder("utf8");
  let collected = "";
  let total = 0;

  try {
    for await (const chunk of requestStream) {
      const buf = Buffer.isBuffer(chunk) ? chunk : Buffer.from(String(chunk), "utf8");
      total += buf.length;
      if (total > MAX_REQ_BYTES) break;
      collected += decoder.write(buf);
    }
    collected += decoder.end();
  } catch {
    writeResponse(responseStream, 400, "Bad Request", "<!doctype html><html><body>Bad Request</body></html>");
    return;
  }

  const username = extractUsernameFromRequestText(collected);
  if (!username || !isValidUsername(username)) {
    writeResponse(responseStream, 400, "Bad Request", "<!doctype html><html><body>Bad Request</body></html>");
    return;
  }

  const safe = htmlEscape(username);
  const body = `<!doctype html><html><body>Hello ${safe}</body></html>`;
  writeResponse(responseStream, 200, "OK", body);
}