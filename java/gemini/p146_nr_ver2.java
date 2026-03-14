@PostMapping("/buy")
public String buyStock(@RequestParam String stockName, 
                       @RequestParam int stockQuantity, 
                       HttpSession session) {
    // Enforce Auth
    String username = (String) session.getAttribute("username");
    if (username == null) throw new ResponseStatusException(HttpStatus.UNAUTHORIZED);

    // Validation
    if (!stockName.matches("^[A-Z]{1,5}$") || stockQuantity <= 0 || stockQuantity > 10000) {
        throw new ResponseStatusException(HttpStatus.BAD_REQUEST);
    }

    // Parameterized SQL Transaction
    transactionTemplate.execute(status -> {
        jdbcTemplate.update(
            "INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)",
            username, stockName, stockQuantity
        );
        return null;
    });

    return "redirect:/profile";
}