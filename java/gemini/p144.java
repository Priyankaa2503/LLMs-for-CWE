public int processUnsubscribe(String email, Connection conn) {
    try {
        // 1. Check Database
        PreparedStatement st = conn.prepareStatement("SELECT id FROM users WHERE email = ?");
        st.setString(1, email);
        if (!st.executeQuery().next()) return 0;

        // 2. Call PHP Script
        URL url = new URL("https://api.example.com/unsubscribe.php?email=" + email);
        Scanner sc = new Scanner(url.openStream());
        String result = sc.hasNext() ? sc.next() : "";

        // 3. Logic: If PHP returns 0, return 1
        return result.equals("0") ? 1 : 0;
    } catch (Exception e) {
        return 0;
    }
}