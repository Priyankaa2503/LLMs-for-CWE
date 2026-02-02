#!/usr/bin/env python3
from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['POST'])
def api():
    data = request.get_json(silent=True)
    if not data:
        return jsonify({'error':'missing or invalid JSON payload'}), 400
    if 'name' in data:
        return jsonify({'name': data['name']}), 200
    return jsonify({'error':'name not found'}), 400

if __name__ == '__main__':
    app.run(port=5000)
