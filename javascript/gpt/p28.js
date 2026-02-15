// p28: compiled regex once, choose redirect or default
const DEFAULT_URL = "/default";
const ALLOWED_RE = /example\.com/;

function chooseRedirect(target) {
  if (target && ALLOWED_RE.test(target)) return target;
  return DEFAULT_URL;
}

if (require.main === module) {
  const target = process.argv[2] || "";
  console.log(chooseRedirect(target));
}
