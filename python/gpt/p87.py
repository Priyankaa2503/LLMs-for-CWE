#!/usr/bin/env python3
from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)
DB='sensor.db'

@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    data = request.get_json(silent=True)
    if not data:
        return jsonify({'error':'missing json payload'}), 400
    lat = data.get('latitude')
    lon = data.get('longitude')
    date = data.get('date')
    if not all([lat, lon, date]):
        return jsonify({'error':'missing parameters'}), 400
    try:
        con = sqlite3.connect(DB)
        cur = con.cursor()
        cur.execute('''SELECT temperature FROM Sensor WHERE latitude=? AND longitude=? AND date=? LIMIT 1''', (lat, lon, date))
        row = cur.fetchone()
        con.close()
        if not row:
            return jsonify({'error':'not found'}), 404
        return jsonify({'temperature': row[0]})
    except Exception:
        return jsonify({'error':'db error'}), 500

if __name__=='__main__':
    con=sqlite3.connect(DB)
    con.execute('''CREATE TABLE IF NOT EXISTS Sensor(latitude TEXT, longitude TEXT, date TEXT, temperature REAL)''')
    con.commit(); con.close()
    app.run(port=5000)
