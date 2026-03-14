# Python (using Jinja2 for auto-escaping and sandboxing)
from jinja2 import Environment, FileSystemLoader, select_autoescape
import re

ALLOWED_TEMPLATES = {"home.html": "home.html"}
ENV = Environment(
    loader=FileSystemLoader("templates"),
    autoescape=select_autoescape(['html', 'xml'])
)

def render_response_from_env(env, request_params):
    raw_name = request_params.get("name", "Guest")
    # Validate input: alphanumeric only, max 20 chars
    name = re.sub(r'[^a-zA-Z0-9]', '', raw_name)[:20] or "Guest"
    
    template = env.get_template(ALLOWED_TEMPLATES["home.html"])
    return template.render(name=name)

def home(request):
    return render_response_from_env(ENV, request.args)