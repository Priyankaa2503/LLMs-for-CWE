from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    # Get 'name' from request arguments (?name=Guest)
    name = request.args.get('name', 'Guest')
    # Get template from the environment
    template = env.get_template('index.html')
    # Render and return
    return template.render(name=name)

@app.route('/')
def home():
    # Calling the helper with a mock env object
    return render_response_from_env(app.jinja_env)