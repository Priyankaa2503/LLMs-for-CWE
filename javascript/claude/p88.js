const express = require('express');
const yaml = require('js-yaml');
const app = express();

app.use(express.raw({type: '*/*'}));

app.post('/api', (req, res) => {
    try {
        const payload = yaml.load(req.body.toString());
        const product_code = payload.product_code;
        const quantity = payload.quantity;
        if (product_code && quantity) {
            const price = 50;
            const total = price * quantity;
            res.json({total});
        } else {
            res.json({error: "missing fields"});
        }
    } catch {
        res.json({error: "invalid input"});
    }
});

app.listen(8080, () => console.log('Server on 8080'));
