from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    # 1. Get name from request
    name = request.args.get('name', 'Guest')
    # 2. Get template from environment
    template = env.from_string("Hello, {{ name }}!")
    # 3. Render and return
    return template.render(name=name)

@app.route('/')
def home():
    # Pass the Jinja environment (app.jinja_env)
    return render_response_from_env(app.jinja_env)