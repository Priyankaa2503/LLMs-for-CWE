// Java (using Pebble Template Engine for auto-escaping)
import com.mitchellbosecke.pebble.PebbleEngine;
import java.util.Map;
import java.util.regex.Pattern;

public class p130_nr_ver2 {
    private static final PebbleEngine engine = new PebbleEngine.Builder().build();
    private static final Pattern VALID_NAME = Pattern.compile("^[a-zA-Z0-9]{0,20}$");

    public String renderResponseFromEnv(Map<String, String> params) {
        String rawName = params.getOrDefault("name", "Guest");
        String name = (VALID_NAME.matcher(rawName).matches()) ? rawName : "Guest";

        java.io.Writer writer = new java.io.StringWriter();
        engine.getTemplate("home.html").evaluate(writer, Map.of("name", name));
        return writer.toString();
    }

    public String home(Map<String, String> params) {
        return renderResponseFromEnv(params);
    }
}