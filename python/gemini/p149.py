from flask import Flask, request, redirect, render_template

app = Flask(__name__)

@app.route('/post', methods=['POST'])
def post_message():
    # Extract data from the request
    username = request.form.get('username')
    message = request.form.get('message')
    
    # Call the DB function
    insert_user_message_in_db(username, message)
    
    # Redirect back to home
    return redirect('/')

@app.route('/')
def index():
    # Fetch messages to display (assuming a fetch function exists)
    messages = get_all_messages()
    return render_template('index.html', messages=messages)