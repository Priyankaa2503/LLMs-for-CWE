const express = require('express');
const app = express();

app.use(express.json());

app.post('/api', (req, res) => {
    const {location, date} = req.body;
    if (location && date) {
        res.json({temperature: 68.0, unit: "F"});
    } else {
        res.json({error: "missing required fields"});
    }
});

app.listen(8080, () => console.log('Server on 8080'));
