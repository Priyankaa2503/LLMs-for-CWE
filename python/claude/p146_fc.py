from flask import Flask, request, session, redirect, url_for
import sqlite3
import re

app = Flask(__name__)
app.secret_key = 'your-secret-key'

@app.route('/buy-stock', methods=['POST'])
def buy_stock():
    # Get username from authenticated session
    username = session.get('username')
    if not username:
        return redirect(url_for('login'))
    
    # Extract and trim form data
    stock_name = request.form.get('stock_name', '').strip()
    stock_quantity = request.form.get('stock_quantity', '').strip()
    
    # Validate stock_name: uppercase letters, digits, hyphens only (1-10 chars)
    if not stock_name or not re.match(r'^[A-Z0-9\-]{1,10}$', stock_name):
        return "Invalid stock name", 400
    
    # Validate stock_quantity: positive integer
    try:
        quantity = int(stock_quantity)
        if quantity <= 0:
            return "Invalid quantity", 400
    except ValueError:
        return "Invalid quantity", 400
    
    # Insert with parameterized query
    try:
        conn = sqlite3.connect('stocks.db')
        cursor = conn.cursor()
        cursor.execute(
            'INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)',
            (username, stock_name, quantity)
        )
        conn.commit()
        conn.close()
    except Exception as e:
        # Log internally, don't expose details
        print(f"Database error: {e}")
        return "Order processing failed", 500
    
    # Redirect to fixed internal route
    return redirect(url_for('profile'))