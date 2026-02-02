const express = require('express');
const app = express();

app.use(express.json());

app.post('/api', (req, res) => {
    const {latitude, longitude, date} = req.body;
    if (latitude && longitude && date) {
        res.json({temperature: 72.5, unit: "F"});
    } else {
        res.json({error: "missing parameters"});
    }
});

app.listen(8080, () => console.log('Server on 8080'));
