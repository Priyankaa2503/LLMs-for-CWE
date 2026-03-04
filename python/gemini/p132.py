from flask import Flask, render_template

app = Flask(__name__)

@app.route('/hello/<username>')
def hello(username):
    # Renders hello.html and passes the username variable
    return render_template('hello.html', username=username)

if __name__ == '__main__':
    app.run(debug=True)