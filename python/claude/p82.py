"""
p82.py
Simple Flask app with /api route that takes a JSON payload and returns the 'name' field.
Run: pip install flask
"""
from flask import Flask, request, jsonify
import json

app = Flask(__name__)

@app.route('/api', methods=['GET', 'POST'])
def api():
    if request.method == 'GET':
        payload = request.args.get('payload')
    else:
        payload = request.form.get('payload') or request.get_json()
    
    if not payload:
        return jsonify({'error': 'missing payload'}), 400
    
    try:
        if isinstance(payload, str):
            data = json.loads(payload)
        else:
            data = payload
        name = data.get('name')
        return jsonify({'name': name})
    except Exception as e:
        return jsonify({'error': str(e)}), 400

if __name__ == '__main__':
    app.run(port=5000)
