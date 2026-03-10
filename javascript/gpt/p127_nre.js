// JavaScript (Node.js readable/writable streams)
import { Buffer } from "node:buffer";

const MAX_USERNAME_LEN = 64;
const USERNAME_RE = /^[A-Za-z0-9_-]{1,64}$/;

function writeResponse(resStream, statusCode, reason, body) {
  const bodyBuf = Buffer.from(body || "", "utf8");
  const header =
    `HTTP/1.1 ${statusCode} ${reason}\r\n` +
    `Content-Type: text/plain; charset=utf-8\r\n` +
    `X-Content-Type-Options: nosniff\r\n` +
    `Content-Length: ${bodyBuf.length}\r\n` +
    `Connection: close\r\n` +
    `\r\n`;
  resStream.write(header, "utf8");
  if (bodyBuf.length) resStream.write(bodyBuf);
  if (typeof resStream.end === "function") resStream.end();
}

function extractUsername(raw) {
  if (typeof raw !== "string" || !raw.length) return null;

  const m = raw.match(/(?:^|[?&\s])username=([^\s&\r\n]+)/);
  if (!m) return null;

  const candidate = m[1];

  // Strict: reject encoding tricks
  if (candidate.includes("%") || candidate.includes("+")) return null;

  if (candidate.length < 1 || candidate.length > MAX_USERNAME_LEN) return null;
  if (!USERNAME_RE.test(candidate)) return null;
  return candidate;
}

export async function http_hello_page(requestStream, responseStream) {
  try {
    let raw = "";
    let total = 0;
    for await (const chunk of requestStream) {
      const buf = Buffer.isBuffer(chunk) ? chunk : Buffer.from(String(chunk), "utf8");
      total += buf.length;
      if (total > 4096) break;
      raw += buf.toString("utf8");
      if (raw.includes("\r\n\r\n") || raw.includes("\n\n")) break;
    }

    const username = extractUsername(raw);
    if (!username) {
      writeResponse(responseStream, 400, "Bad Request", "Bad Request\n");
      return;
    }

    writeResponse(responseStream, 200, "OK", `Hello ${username}\n`);
  } catch {
    writeResponse(responseStream, 400, "Bad Request", "Bad Request\n");
  }
}