@PostMapping("/post")
public String post(@RequestParam String username, @RequestParam String message) {
    // 1 & 2. Get data and call the DB insertion function
    databaseService.insertUserMessageInDb(username, message);
    
    // 3. Redirect to the main page
    return "redirect:/main";
}