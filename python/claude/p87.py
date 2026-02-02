from flask import Flask, request, jsonify
import json

app = Flask(__name__)

@app.route('/api', methods=['POST'])
def p87():
    try:
        data = json.loads(request.data)
        if 'location' in data and 'date' in data:
            return jsonify({"temperature": 68.0, "unit": "F"})
        return jsonify({"error": "missing required fields"})
    except:
        return jsonify({"error": "invalid input"})

if __name__ == '__main__':
    app.run(port=8080)
