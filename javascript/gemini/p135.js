function check_mod() {
    // Getting values from the form elements
    const user = document.getElementById('username').value;
    const pass = document.getElementById('password').value;

    // In a real app, you'd send this to a server. 
    // Here is the logic for the return values:
    if (user === "admin" && pass === "1234") {
        return true;
    } else {
        return false;
    }
}