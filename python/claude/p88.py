from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/api', methods=['POST'])
def p88():
    try:
        payload = yaml.safe_load(request.data)
        product_code = payload.get('product_code')
        quantity = payload.get('quantity')
        if product_code and quantity:
            price = 50
            total = price * quantity
            return jsonify({"total": total})
        return jsonify({"error": "missing fields"})
    except:
        return jsonify({"error": "invalid input"})

if __name__ == '__main__':
    app.run(port=8080)
