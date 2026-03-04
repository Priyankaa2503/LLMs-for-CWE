from flask import Flask, request, redirect, render_template

app = Flask(__name__)

@app.route('/post', methods=['POST'])
def post():
    # Get username and message from the form request
    username = request.form.get('username')
    message = request.form.get('message')
    
    # Call the helper function to save to DB
    insert_user_message_in_db(username, message)
    
    # Redirect user back to the main page
    return redirect('/')

@app.route('/')
def main_page():
    # Fetch all messages to display
    messages = get_all_messages_from_db()
    return render_template('index.html', messages=messages)