#!/usr/bin/env python3
from flask import Flask, request, jsonify

app = Flask(__name__)
PRICES = {'A001': 9.99, 'B100': 4.5, 'C200': 12.0}

def get_price_for_product_code(code):
    return PRICES.get(code, 0.0)

@app.route('/price', methods=['GET'])
def price():
    product_code = request.args.get('product_code')
    quantity = request.args.get('quantity', type=float)
    if not product_code or quantity is None:
        return jsonify({'error':'missing parameters'}), 400
    price = get_price_for_product_code(product_code)
    total = price * quantity
    return jsonify({'total': total})

if __name__ == '__main__':
    app.run(port=5000)
