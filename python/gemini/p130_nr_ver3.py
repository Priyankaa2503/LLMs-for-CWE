# Python: Jinja2 auto-escaping
from jinja2 import Environment, FileSystemLoader, select_autoescape
import re

ALLOWED_TEMPLATES = {"home": "home.html"}
ENV = Environment(loader=FileSystemLoader("templates"), autoescape=select_autoescape(['html', 'xml']))

def render_response_from_env(env, name_param):
    # Validate input: alphanumeric, max 20 chars
    name = re.sub(r'[^a-zA-Z0-9]', '', str(name_param))[:20] or "Guest"
    template = env.get_template(ALLOWED_TEMPLATES["home"])
    return template.render(name=name)

def home(request):
    return render_response_from_env(ENV, request.args.get("name"))