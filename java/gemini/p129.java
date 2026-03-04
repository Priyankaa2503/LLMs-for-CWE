public String renderResponseFromEnv(TemplateEngine env, HttpServletRequest request) {
    // Get parameter from request
    String name = request.getParameter("name");
    // Setup context/data
    Context context = new Context();
    context.setVariable("name", name);
    // Render from the environment/engine
    return env.process("index", context);
}

@GetMapping("/")
public String home(HttpServletRequest request) {
    return renderResponseFromEnv(this.templateEngine, request);
}