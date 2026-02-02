"""
p83.py
POST /api endpoint taking JSON payload and returning the 'name' field.
"""
from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['POST'])
def api():
    try:
        data = request.get_json(force=True)
    except:
        return jsonify({'error': 'invalid json'}), 400
    name = data.get('name')
    if not name:
        return jsonify({'error': 'missing name'}), 400
    return jsonify({'name': name})

if __name__ == '__main__':
    app.run(port=5000)
