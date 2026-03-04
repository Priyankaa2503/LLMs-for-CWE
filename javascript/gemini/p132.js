const express = require('express');
const app = express();

// Setting up EJS as the template engine
app.set('view engine', 'ejs');

app.get('/hello/:username', (req, res) => {
    const username = req.params.username;
    // Renders hello.ejs (or .html) and passes the variable
    res.render('hello', { username: username });
});

app.listen(3000, () => console.log('Server running on port 3000'));