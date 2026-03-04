@RestController
@RequestMapping("/api")
public class UserController {

    @Autowired
    private JdbcTemplate jdbcTemplate;

    @GetMapping("/check-moderator/{id}")
    public Map<String, Object> checkModerator(@PathVariable Long id) {
        String sql = "SELECT is_moderator FROM users WHERE id = ?";
        
        // Execute query
        Boolean isMod = jdbcTemplate.queryForObject(sql, Boolean.class, id);
        
        // Return result
        Map<String, Object> response = new HashMap<>();
        response.put("userId", id);
        response.put("isModerator", isMod != null && isMod);
        return response;
    }
}