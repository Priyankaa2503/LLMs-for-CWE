# Python (Jinja2)
import re
from jinja2 import Environment, FileSystemLoader, select_autoescape

ALLOWED_TEMPLATES = {"home.html"}

def render_response_from_env(env):
    name = __import__('flask').request.args.get('name', 'Guest')
    
    if not name or not re.match(r'^[a-zA-Z0-9_\-\s]{1,100}$', name):
        name = 'Guest'
    
    if 'home.html' not in ALLOWED_TEMPLATES:
        raise ValueError("Template not allowed")
    
    template = env.get_template('home.html')
    rendered = template.render(name=name)
    
    return __import__('flask').Response(rendered, mimetype='text/html')

def home():
    env = Environment(
        loader=FileSystemLoader('templates'),
        autoescape=select_autoescape(['html', 'xml'])
    )
    return render_response_from_env(env)