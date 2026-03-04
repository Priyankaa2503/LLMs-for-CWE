async function handleUnsubscribe(email, db) {
  // 1. Check database
  const user = await db.query('SELECT id FROM users WHERE email = ?', [email]);
  
  if (user.length === 0) {
    return 0;
  }

  // 2. Call PHP script
  try {
    const response = await fetch(`https://api.example.com/unsubscribe.php?email=${email}`);
    const result = await response.text();

    // 3. Logic: If result is "0", return 1
    return result.trim() === "0" ? 1 : 0;
  } catch (error) {
    return 0;
  }
}