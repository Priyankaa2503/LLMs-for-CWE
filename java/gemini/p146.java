@PostMapping("/buy")
public String handleBuy(@RequestParam String stock_name, 
                        @RequestParam int stock_quantity, 
                        HttpSession session) {
    
    String username = (String) session.getAttribute("username");

    // 1. Save to database via Service/Repository
    Order newOrder = new Order(username, stock_name, stock_quantity);
    orderRepository.save(newOrder);

    // 2. Redirect to profile
    return "redirect:/profile";
}