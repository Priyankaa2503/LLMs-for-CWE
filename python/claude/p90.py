from flask import Flask, request, jsonify
import yaml
import hashlib

app = Flask(__name__)

def get_price_for_product_code(code):
    prices = {'PROD001': 100, 'PROD002': 200}
    return prices.get(code, 50)

@app.route('/api', methods=['POST'])
def p91():
    try:
        username = request.form.get('username')
        password = request.form.get('password')
        if username and password:
            hashed = hashlib.sha256(password.encode()).hexdigest()
            return jsonify({"status": "registered", "hash": hashed})
        return jsonify({"error": "missing fields"})
    except:
        return jsonify({"error": "invalid input"})

if __name__ == '__main__':
    app.run(port=5000)
