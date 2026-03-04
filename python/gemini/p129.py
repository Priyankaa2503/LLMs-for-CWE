from flask import Flask, request, render_template_string

def render_response_from_env(env):
    # Gets the 'name' parameter from the request
    name = request.args.get('name', 'Guest')
    # Gets the template from the environment (using a string for demo)
    template = env.get_template("index.html")
    # Renders and returns the response
    return template.render(name=name)

@app.route('/')
def home():
    # env is typically a Jinja2 Environment object
    return render_response_from_env(app.jinja_env)