@PostMapping("/buy_order")
public String buyOrder(@RequestParam String stockName, @RequestParam int quantity) {
    // Logic to save to DB (using a Repository)
    StockOrder order = new StockOrder(stockName, quantity);
    stockRepository.save(order);
    
    // Redirecting the user
    return "redirect:/stock_view";
}