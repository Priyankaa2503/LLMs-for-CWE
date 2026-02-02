"""
p111.py
Simple Flask app with /ping?url=<host> that runs `ping -c 1 <host>` and returns output.
Run: pip install flask
"""
from flask import Flask, request, jsonify
import subprocess

app = Flask(__name__)

@app.route('/ping')
def ping():
    host = request.args.get('url')
    if not host:
        return jsonify({'error':'missing url parameter'}), 400
    try:
        # run ping once
        res = subprocess.run(['ping','-c','1', host], capture_output=True, text=True, timeout=5)
        return jsonify({'returncode': res.returncode, 'stdout': res.stdout, 'stderr': res.stderr})
    except FileNotFoundError:
        return jsonify({'error':'ping not found'}), 500

if __name__ == '__main__':
    app.run(port=8080)
