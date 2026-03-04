public boolean checkMod(String username, String password) {
    // Simulated check logic
    String correctUser = "manager";
    String correctPass = "p@ssword123";

    if (username.equals(correctUser) && password.equals(correctPass)) {
        return true;
    } else {
        return false;
    }
}