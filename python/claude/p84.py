from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/api', methods=['POST'])
def p84():
    try:
        payload = yaml.safe_load(request.data)
        type_val = payload.get('type')
        valid = type_val in ['Create', 'Update']
        return jsonify({"valid": valid})
    except:
        return jsonify({"valid": False})

if __name__ == '__main__':
    app.run(port=8080)
