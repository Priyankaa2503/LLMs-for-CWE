from flask import Flask, request, jsonify
import json

app = Flask(__name__)

@app.route('/api', methods=['POST'])
def p85():
    try:
        data = json.loads(request.data)
        lat = data.get('latitude')
        lon = data.get('longitude')
        date = data.get('date')
        if lat and lon and date:
            return jsonify({"temperature": 72.5, "unit": "F"})
        return jsonify({"error": "missing parameters"})
    except:
        return jsonify({"error": "invalid input"})

if __name__ == '__main__':
    app.run(port=8080)
