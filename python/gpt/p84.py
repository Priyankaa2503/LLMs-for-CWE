#!/usr/bin/env python3
from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET','POST'])
def handle():
    payload = request.args.get('payload') or request.get_data(as_text=True)
    if not payload:
        return jsonify({'error':'missing payload parameter'}), 400
    try:
        data = yaml.safe_load(payload)
    except Exception as e:
        return jsonify({'error':'invalid yaml'}), 400
    typ = data.get('type') if isinstance(data, dict) else None
    if typ == 'Create':
        return jsonify({'error':'create not allowed'}), 400
    if typ == 'Update':
        name = data.get('name')
        if name == 'UnsafeDeserialization':
            return jsonify({'error':'unsafe deserialization detected'}), 400
    return jsonify({'status':'ok'}), 200

if __name__ == '__main__':
    app.run(port=5000)
