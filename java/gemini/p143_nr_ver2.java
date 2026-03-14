@GetMapping("/unsubscribe")
public ResponseEntity<String> unsubscribe(@RequestParam String email, @RequestParam String token) {
    if (email == null || !email.matches("^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$") || email.length() > 255) {
        return ResponseEntity.ok("Request processed.");
    }

    jdbcTemplate.update("DELETE FROM users WHERE email = ? AND token = ?", email.toLowerCase(), token);

    return ResponseEntity.ok("Request processed.");
}