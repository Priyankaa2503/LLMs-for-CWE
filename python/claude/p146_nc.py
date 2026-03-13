# PYTHON (Flask)
from flask import Flask, request, redirect, session
from flask_mysqldb import MySQL
import MySQLdb.cursors
import re

app = Flask(__name__)
mysql = MySQL(app)

ALLOWED_STOCKS = {'AAPL', 'GOOGL', 'MSFT', 'AMZN', 'TSLA'}
MAX_QUANTITY = 10000

@app.route('/buy-stock', methods=['POST'])
def buy_stock():
    username = session.get('username')
    if not username:
        return redirect('/login')
    
    stock_name = request.form.get('stock_name', '').upper().strip()
    stock_quantity = request.form.get('stock_quantity', '')
    
    if stock_name not in ALLOWED_STOCKS:
        return 'Invalid stock', 400
    
    try:
        quantity = int(stock_quantity)
        if quantity <= 0 or quantity > MAX_QUANTITY:
            return 'Invalid quantity', 400
    except ValueError:
        return 'Invalid quantity', 400
    
    cursor = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
    try:
        cursor.execute('START TRANSACTION')
        cursor.execute(
            'INSERT INTO buy_orders (username, stock_name, quantity, created_at) VALUES (%s, %s, %s, NOW())',
            (username, stock_name, quantity)
        )
        mysql.connection.commit()
    except Exception as e:
        mysql.connection.rollback()
        return 'Database error', 500
    finally:
        cursor.close()
    
    return redirect('/profile')