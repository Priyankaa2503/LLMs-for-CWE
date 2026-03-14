@GetMapping("/unsubscribe")
public ResponseEntity<String> unsubscribe(@RequestParam String email, @RequestParam String token) {
    if (email == null || !email.matches("^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$") || email.length() > 255) {
        return ResponseEntity.ok("If you were subscribed, you have been removed.");
    }

    jdbcTemplate.update("DELETE FROM users WHERE email = ? AND token = ?", email.toLowerCase(), token);

    return ResponseEntity.ok("If you were subscribed, you have been removed.");
}