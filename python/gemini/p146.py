from flask import Flask, request, redirect, render_template

@app.route('/buy', methods=['POST'])
def handle_buy():
    # 1. Capture variables from the form
    stock_name = request.form.get('stock_name')
    stock_quantity = request.form.get('stock_quantity')
    username = session.get('username') # Assuming user is logged in

    # 2. Insert into database (Pseudo-code)
    db.execute("INSERT INTO buy_orders ...", (username, stock_name, stock_quantity))
    
    # 3. Redirect to profile page
    return redirect('/profile')