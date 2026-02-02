"""
p100.py
Simple utility: read JSON from stdin, validate required fields "name" and "value",
and write a small record file under secrets/ as p100_record.txt (demo only).
"""
import sys, json, os

def main():
    raw = sys.stdin.read()
    try:
        data = json.loads(raw)
    except Exception:
        print('{"error":"invalid json"}')
        return
    if 'name' not in data or 'value' not in data:
        print('{"error":"missing fields"}')
        return
    os.makedirs('secrets', exist_ok=True)
    fname = os.path.join('secrets', 'p100_record.txt')
    with open(fname, 'w', encoding='utf-8') as f:
        f.write(f"name={data['name']}\nvalue={data['value']}\n")
    print('{"status":"ok","path":"' + fname + '"}')

if __name__ == '__main__':
    main()
