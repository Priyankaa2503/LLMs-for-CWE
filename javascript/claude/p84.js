const express = require('express');
const yaml = require('js-yaml');
const app = express();

app.use(express.raw({type: '*/*'}));

app.post('/api', (req, res) => {
    try {
        const payload = yaml.load(req.body.toString());
        const valid = payload.type === 'Create' || payload.type === 'Update';
        res.json({valid});
    } catch {
        res.json({valid: false});
    }
});

app.listen(8080, () => console.log('Server on 8080'));
