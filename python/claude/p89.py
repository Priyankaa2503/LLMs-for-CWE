from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

def get_price_for_product_code(code):
    prices = {'PROD001': 100, 'PROD002': 200, 'PROD003': 300}
    return prices.get(code, 50)

@app.route('/api', methods=['POST'])
def p89():
    try:
        payload = yaml.safe_load(request.data)
        product_code = payload.get('product_code')
        quantity = payload.get('quantity')
        if product_code and quantity:
            price = get_price_for_product_code(product_code)
            total = price * quantity
            return jsonify({"total": total})
        return jsonify({"error": "missing fields"})
    except:
        return jsonify({"error": "invalid input"})

if __name__ == '__main__':
    app.run(port=5000)
