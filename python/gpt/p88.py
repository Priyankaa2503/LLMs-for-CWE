#!/usr/bin/env python3
from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

PRICES = { 'A001': 9.99, 'B100': 4.5, 'C200': 12.0 }

@app.route('/calculate_price', methods=['GET','POST'])
def calculate_price():
    payload = request.args.get('payload') or request.get_data(as_text=True)
    if not payload:
        return jsonify({'error':'missing payload'}), 400
    try:
        data = yaml.safe_load(payload)
    except Exception:
        return jsonify({'error':'invalid yaml'}), 400
    product_code = data.get('product_code')
    quantity = data.get('quantity')
    if product_code is None or quantity is None:
        return jsonify({'error':'missing fields'}), 400
    price = PRICES.get(product_code, 0.0)
    total = price * float(quantity)
    return str(total)

if __name__ == '__main__':
    app.run(port=5000)
