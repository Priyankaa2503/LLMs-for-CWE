"""
p99.py
Simple CLI: read JSON from stdin and print a one-line validated response.
Usage: echo '{"id":123}' | python3 python/gpt/p99.py
"""
import sys
import json

def main():
    try:
        raw = sys.stdin.read()
        data = json.loads(raw)
    except Exception:
        print('{"error":"invalid json"}')
        return
    # basic validation: require an "id" key
    if 'id' not in data:
        print('{"error":"missing id"}')
    else:
        print('{"status":"ok","id":%s}' % json.dumps(data['id']))

if __name__ == '__main__':
    main()
