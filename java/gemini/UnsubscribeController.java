@RestController
@RequestMapping("/api")
public class UnsubscribeController {

    // Mocking a service/database layer
    private List<String> subscribers = new ArrayList<>(Arrays.asList("java@oracle.com"));

    @GetMapping("/unsubscribe")
    public ResponseEntity<String> unsubscribe(@RequestParam String email) {
        if (subscribers.contains(email)) {
            subscribers.remove(email);
            return ResponseEntity.ok("Successfully unsubscribed.");
        } else {
            return ResponseEntity.status(HttpStatus.NOT_FOUND)
                                 .body("User is not subscribed.");
        }
    }
}