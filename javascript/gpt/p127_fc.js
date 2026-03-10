// JavaScript (Node.js Readable/Writable streams)
import { URL } from "node:url";

function isValidUsername(u) {
  return typeof u === "string" && /^[A-Za-z0-9_-]{1,32}$/.test(u);
}

function writeResponse(res, statusCode, body) {
  const statusText = statusCode === 200 ? "OK" : "Bad Request";
  const buf = Buffer.isBuffer(body) ? body : Buffer.from(String(body), "utf8");
  const headers =
    `HTTP/1.1 ${statusCode} ${statusText}\r\n` +
    `Content-Type: text/plain; charset=utf-8\r\n` +
    `X-Content-Type-Options: nosniff\r\n` +
    `Cache-Control: no-store\r\n` +
    `Content-Length: ${buf.length}\r\n` +
    `\r\n`;
  res.write(headers, "utf8");
  res.write(buf);
  if (typeof res.end === "function") res.end();
}

export function http_hello_page(request_stream, response_stream) {
  const MAX = 8192;
  const chunks = [];
  let total = 0;
  let done = false;

  const finish = (raw) => {
    if (done) return;
    done = true;

    const text = raw.toString("latin1");
    if (!text.includes("\r\n")) {
      writeResponse(response_stream, 400, "Bad Request");
      return;
    }

    const [head, body = ""] = text.split("\r\n\r\n", 2);
    const requestLine = head.split("\r\n", 1)[0] || "";
    const parts = requestLine.split(" ");
    const target = parts.length >= 2 ? parts[1] : "";

    let username = null;

    try {
      // Use a dummy base for relative URLs
      const u = new URL(target, "http://localhost/");
      username = u.searchParams.get("username");
    } catch {
      username = null;
    }

    if (!username && body) {
      // Parse application/x-www-form-urlencoded body safely
      try {
        const params = new URLSearchParams(body);
        username = params.get("username");
      } catch {
        username = null;
      }
    }

    if (!isValidUsername(username)) username = "friend";
    writeResponse(response_stream, 200, `Hello ${username}`);
  };

  request_stream.on("data", (chunk) => {
    if (done) return;
    total += chunk.length;
    if (total > MAX) {
      // Cap input; proceed with what we have (no detailed error leakage)
      finish(Buffer.concat(chunks));
      return;
    }
    chunks.push(chunk);
  });

  request_stream.on("end", () => finish(Buffer.concat(chunks)));
  request_stream.on("error", () => writeResponse(response_stream, 400, "Bad Request"));
}