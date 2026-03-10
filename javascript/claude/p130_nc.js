const ejs = require('ejs');
const path = require('path');

async function render_response_from_env(env) {
    // Get name parameter with validation
    let name = env.query.name || 'Guest';
    
    // Sanitize: allow alphanumeric and spaces only
    if (!/^[a-zA-Z0-9\s]*$/.test(name)) {
        name = 'Guest';
    }
    
    // Template is fixed and allowlisted
    const templatePath = path.join(__dirname, 'views', 'greeting.ejs');
    
    // Render template with auto-escaping (EJS default)
    const rendered = await ejs.renderFile(templatePath, { name });
    
    return {
        statusCode: 200,
        contentType: 'text/html',
        body: rendered
    };
}

async function home(env) {
    // Home endpoint calls render function
    return await render_response_from_env(env);
}