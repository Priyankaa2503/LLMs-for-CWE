from flask import Flask, request, redirect, url_base
import sqlite3

app = Flask(__name__)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    # 1. Get data from the form
    stock = request.form.get('stock_name')
    qty = request.form.get('quantity')

    # 2. Insert into database
    conn = sqlite3.connect('market.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO stock_orders (stock_name, quantity) VALUES (?, ?)", (stock, qty))
    conn.commit()
    conn.close()

    # 3. Redirect to the view page
    return redirect('/stock_view')