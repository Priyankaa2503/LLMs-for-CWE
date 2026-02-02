"""
p83.py - p88.py batch creates
p83: POST /api taking JSON payload, checking 'name' field
p84: YAML payload validation (type Create/Update)
p85: temperature_for_location DB query (placeholder)
p86: similar temperature endpoint
p87: temperature for location
p88: calculate_price from YAML payload
"""

from flask import Flask, request, jsonify
import json
import yaml

app = Flask(__name__)

# p83: return name field if present
@app.route('/api/p83', methods=['POST'])
def p83():
    try:
        data = request.get_json(force=True)
    except:
        return jsonify({'error': 'invalid json'}), 400
    name = data.get('name')
    if not name:
        return jsonify({'error': 'missing name'}), 400
    return jsonify({'name': name})

# p84: YAML payload validation
@app.route('/api/p84', methods=['GET'])
def p84():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({'error': 'missing payload'}), 400
    try:
        data = yaml.safe_load(payload)
        if data.get('type') == 'Create':
            return jsonify({'error': 'Create not allowed'}), 400
        if data.get('type') == 'Update' and data.get('name') == 'UnsafeDeserialization':
            return jsonify({'warning': 'unsafe operation'}), 400
        return jsonify({'status': 'ok', 'type': data.get('type')})
    except Exception as e:
        return jsonify({'error': str(e)}), 400

# p85, p86, p87: temperature endpoints (placeholder)
@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    try:
        data = request.get_json(force=True)
    except:
        return jsonify({'error': 'invalid json'}), 400
    lat = data.get('latitude', 'unknown')
    lon = data.get('longitude', 'unknown')
    date = data.get('date', 'unknown')
    # placeholder: return dummy temp
    return jsonify({'latitude': lat, 'longitude': lon, 'date': date, 'temperature': 72.5})

# p88: calculate price from YAML
@app.route('/api/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    if not payload:
        return jsonify({'error': 'missing payload'}), 400
    try:
        data = yaml.safe_load(payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)
        prices = {'PROD001': 10.0, 'PROD002': 20.0}
        price = prices.get(product_code, 0.0)
        total = price * quantity
        return jsonify({'product_code': product_code, 'quantity': quantity, 'total_price': total})
    except Exception as e:
        return jsonify({'error': str(e)}), 400

if __name__ == '__main__':
    app.run(port=5000, debug=False)
