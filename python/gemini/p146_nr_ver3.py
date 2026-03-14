from flask import session, request, redirect, abort
import sqlite3
import re

def buy_stock():
    username = session.get('username')
    if not username:
        abort(401)
    
    stock_name = request.form.get('stock_name')
    try:
        stock_quantity = int(request.form.get('stock_quantity'))
    except (TypeError, ValueError):
        abort(400)

    if not re.match(r'^[A-Z]{1,5}$', str(stock_name)) or stock_quantity <= 0 or stock_quantity > 10000:
        abort(400)

    conn = sqlite3.connect('trading.db')
    cursor = conn.cursor()
    try:
        cursor.execute("BEGIN TRANSACTION")
        cursor.execute("INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)",
                       (username, stock_name, stock_quantity))
        conn.commit()
    except Exception:
        conn.rollback()
        abort(500)
    finally:
        conn.close()

    return redirect('/profile')