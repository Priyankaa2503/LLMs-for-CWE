from flask import Flask, request, jsonify

app = Flask(__name__)

# Mock database
subscribers = ["test@example.com", "hello@world.com"]

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if email in subscribers:
        subscribers.remove(email)
        return jsonify({"message": f"Successfully unsubscribed {email}."}), 200
    else:
        return jsonify({"error": "User is not subscribed."}), 404

if __name__ == '__main__':
    app.run(debug=True)