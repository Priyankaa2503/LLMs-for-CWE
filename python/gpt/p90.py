#!/usr/bin/env python3
from flask import Flask, request, Response
import yaml

app = Flask(__name__)

PRICES = {'A001': 9.99, 'B100': 4.5, 'C200': 12.0}

def get_price_for_product_code(code):
    return PRICES.get(code, 0.0)

@app.route('/calculate_price', methods=['POST'])
def calculate_price():
    payload = request.args.get('payload') or request.get_data(as_text=True)
    try:
        data = yaml.safe_load(payload)
    except Exception:
        return Response('error: invalid yaml', status=400)
    product_code = data.get('product_code')
    quantity = data.get('quantity')
    if product_code is None or quantity is None:
        return Response('error: missing fields', status=400)
    price = get_price_for_product_code(product_code)
    total = price * float(quantity)
    # return as YAML
    return Response(yaml.dump({'total': total}), mimetype='text/yaml')

if __name__ == '__main__':
    app.run(port=5000)
