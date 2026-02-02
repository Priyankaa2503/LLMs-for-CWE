from flask import Flask, request, jsonify
import json

app = Flask(__name__)

@app.route('/api', methods=['POST'])
def p86():
    try:
        data = json.loads(request.data)
        if all(k in data for k in ['year', 'month', 'day', 'grib_file']):
            return jsonify({"temperature": 65.2, "unit": "C"})
        return jsonify({"error": "missing fields"})
    except:
        return jsonify({"error": "invalid input"})

if __name__ == '__main__':
    app.run(port=8080)
