#!/usr/bin/env python3
from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)
DB = 'sensor.db'

@app.route('/api/temperature_for_location', methods=['GET','POST'])
def temperature():
    # accept query params or JSON body
    data = request.get_json(silent=True) or {}
    lat = data.get('latitude') or request.args.get('latitude')
    lon = data.get('longitude') or request.args.get('longitude')
    year = data.get('year') or request.args.get('year')
    month = data.get('month') or request.args.get('month')
    day = data.get('day') or request.args.get('day')
    grib = data.get('grib_file') or request.args.get('grib_file')
    if not all([lat, lon, year, month, day, grib]):
        return jsonify({'error':'missing parameters'}), 400
    try:
        con = sqlite3.connect(DB)
        cur = con.cursor()
        cur.execute('''SELECT MAX(temperature) FROM Sensor WHERE latitude=? AND longitude=? AND year=? AND month=? AND day=? AND grib_file=?''', (lat, lon, year, month, day, grib))
        row = cur.fetchone()
        con.close()
        if not row or row[0] is None:
            return jsonify({'error':'not found'}), 404
        return jsonify({'max_temperature': row[0]})
    except Exception:
        return jsonify({'error':'db error'}), 500

if __name__ == '__main__':
    # ensure table exists
    con = sqlite3.connect(DB)
    con.execute('''CREATE TABLE IF NOT EXISTS Sensor(latitude TEXT, longitude TEXT, year TEXT, month TEXT, day TEXT, grib_file TEXT, temperature REAL)''')
    con.commit()
    con.close()
    app.run(port=5000)
