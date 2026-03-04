const express = require('express');
const app = express();

let subscribers = ["dev@example.com", "code@js.com"];

app.get('/unsubscribe', (req, res) => {
    const email = req.query.email;
    const index = subscribers.indexOf(email);

    if (index !== -1) {
        subscribers.splice(index, 1); // Delete from list
        res.status(200).send(`User ${email} has been unsubscribed.`);
    } else {
        res.status(404).send("User is not subscribed.");
    }
});

app.listen(3000, () => console.log('Server running on port 3000'));