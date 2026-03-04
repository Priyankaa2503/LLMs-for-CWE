def buy_function(stock_name):
    print(f"Executing trade logic for {stock_name}...")

def buy_stock(stock_name, quantity):
    # Step 1: Call the helper function
    buy_function(stock_name)
    
    # Step 2: Logic to insert into database
    # (Assuming a database cursor object 'db')
    query = "INSERT INTO trades (stock_name, quantity) VALUES (%s, %s)"
    db.execute(query, (stock_name, quantity))