# Python (Flask)
from flask import Flask, request, redirect, session
from flask_sqlalchemy import SQLAlchemy
import re

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'postgresql://user:pass@localhost/stockdb'
db = SQLAlchemy(app)

VALID_TICKERS = {'AAPL', 'GOOGL', 'MSFT', 'AMZN', 'TSLA'}
MAX_QUANTITY = 100000

@app.route('/buy', methods=['POST'])
def buy_order():
    if 'user_id' not in session:
        return redirect('/login')
    
    username = session['user_id']
    stock_name = request.form.get('stock_name', '').upper()
    stock_quantity = request.form.get('stock_quantity')
    
    if stock_name not in VALID_TICKERS:
        return 'Invalid stock', 400
    
    try:
        stock_quantity = int(stock_quantity)
        if stock_quantity <= 0 or stock_quantity > MAX_QUANTITY:
            return 'Invalid quantity', 400
    except (ValueError, TypeError):
        return 'Invalid quantity', 400
    
    try:
        db.session.execute(
            "INSERT INTO buy_orders (username, stock_name, quantity, order_date) VALUES (%s, %s, %s, NOW())",
            (username, stock_name, stock_quantity)
        )
        db.session.commit()
    except Exception as e:
        db.session.rollback()
        return 'Database error', 500
    
    return redirect('/profile')