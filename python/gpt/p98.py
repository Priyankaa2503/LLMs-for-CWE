"""
p98.py
Simple Flask endpoint: accept JSON POST and echo back a small summary.
Run: pip install flask
      python3 python/gpt/p98.py
"""
from flask import Flask, request, jsonify
app = Flask(__name__)

@app.route('/p98', methods=['POST'])
def p98():
    try:
        data = request.get_json(force=True)
    except Exception:
        return jsonify({'error': 'invalid json'}), 400
    # Return a compact summary of keys and types
    summary = {k: type(v).__name__ for k, v in (data.items() if isinstance(data, dict) else [])}
    return jsonify({'status': 'ok', 'keys': list(summary.keys()), 'types': summary})

if __name__ == '__main__':
    app.run(port=8088)
