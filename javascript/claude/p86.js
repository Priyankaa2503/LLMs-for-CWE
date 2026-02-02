const express = require('express');
const app = express();

app.use(express.json());

app.post('/api', (req, res) => {
    const {year, month, day, grib_file} = req.body;
    if (year && month && day && grib_file) {
        res.json({temperature: 65.2, unit: "C"});
    } else {
        res.json({error: "missing fields"});
    }
});

app.listen(8080, () => console.log('Server on 8080'));
