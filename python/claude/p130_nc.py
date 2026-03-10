from jinja2 import Environment, FileSystemLoader, select_autoescape

def render_response_from_env(env):
    """Render template with name parameter from request"""
    # Get name parameter with validation
    name = request.args.get('name', 'Guest')
    
    # Sanitize: allow alphanumeric and spaces only
    if not all(c.isalnum() or c.isspace() for c in name):
        name = 'Guest'
    
    # Template is fixed and allowlisted
    template_name = 'greeting.html'
    
    # Get template from environment with auto-escaping enabled
    template = env.get_template(template_name)
    
    # Render with name parameter
    rendered = template.render(name=name)
    
    return Response(rendered, mimetype='text/html')

def home(env):
    """Home endpoint"""
    return render_response_from_env(env)

# Setup environment with auto-escaping
jinja_env = Environment(
    loader=FileSystemLoader('templates'),
    autoescape=select_autoescape(['html', 'xml'])
)