#!/usr/bin/env python3
from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)
DB = 'sensor.db'

def get_temperature(lat, lon, date):
    # simple example: connect to sqlite and query a Sensor table
    try:
        con = sqlite3.connect(DB)
        cur = con.cursor()
        cur.execute('''SELECT temperature FROM Sensor WHERE latitude=? AND longitude=? AND date=? LIMIT 1''', (lat, lon, date))
        row = cur.fetchone()
        con.close()
        return row[0] if row else None
    except Exception:
        return None

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
    temp = get_temperature(lat, lon, date)
    if temp is None:
        return jsonify({'error':'not found'}), 404
    return jsonify({'temperature': temp})

if __name__ == '__main__':
    # create DB and table if not exists (example)
    con = sqlite3.connect(DB)
    con.execute('''CREATE TABLE IF NOT EXISTS Sensor (latitude TEXT, longitude TEXT, date TEXT, temperature REAL)''')
    con.commit()
    con.close()
    app.run(port=5000)
