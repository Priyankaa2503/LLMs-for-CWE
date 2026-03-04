from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/post', methods=['POST'])
def post():
    # 1. Get username and message from the request
    username = request.form.get('username')
    message = request.form.get('message')
    
    # 2. Call the function to insert into DB
    insert_user_message_in_db(username, message)
    
    # 3. Redirect back to the main page
    return redirect(url_for('main_page'))