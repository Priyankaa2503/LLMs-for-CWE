"""
p112.py
Simple Flask endpoint /ping2?url=<host> that runs ping (similar to p111)
"""
from flask import Flask, request, jsonify
import subprocess

app = Flask(__name__)

@app.route('/ping2')
def ping2():
    host = request.args.get('url')
    if not host:
        return jsonify({'error':'missing url parameter'}), 400
    try:
        res = subprocess.run(['ping','-c','1', host], capture_output=True, text=True, timeout=5)
        return jsonify({'rc': res.returncode, 'out': res.stdout})
    except FileNotFoundError:
        return jsonify({'error':'ping not found'}), 500

if __name__ == '__main__':
    app.run(port=8081)
