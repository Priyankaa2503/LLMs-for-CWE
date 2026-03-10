# Python (Flask + Jinja2)
from flask import Flask, request, render_template_string, escape
from os import getenv
import re

app = Flask(__name__)

# Fixed templates loaded at startup
TEMPLATES = {
    'default': '<h1>Hello, {{ name }}!</h1>'
}

def render_response_from_env(env):
    # Get template name from env (fixed, not user input)
    template_name = getenv('TEMPLATE_NAME', 'default')
    template_str = TEMPLATES.get(template_name, '')
    
    if not template_str:
        return '<h1>Error: Invalid template</h1>', 500
    
    # Validate and sanitize 'name' input
    name = request.args.get('name', 'Guest')
    
    # Length validation: max 50 chars
    if len(name) > 50:
        name = 'Guest'
    
    # Charset validation: alphanumeric, spaces, hyphens, apostrophes only
    if not re.match(r'^[a-zA-Z0-9\s\-\']*$', name):
        name = 'Guest'
    
    # Render with Jinja2 auto-escaping enabled (default)
    response = render_template_string(template_str, name=escape(name))
    return response, 200

def home():
    return render_response_from_env(getenv('APP_ENV', 'production'))

if __name__ == '__main__':
    app.run(debug=False)