const express = require('express');
const yaml = require('js-yaml');
const app = express();

app.use(express.raw({type: '*/*'}));

function getPriceForProductCode(code) {
    const prices = {'PROD001': 100, 'PROD002': 200, 'PROD003': 300};
    return prices[code] || 50;
}

app.post('/api', (req, res) => {
    try {
        const payload = yaml.load(req.body.toString());
        const product_code = payload.product_code;
        const quantity = payload.quantity;
        if (product_code && quantity) {
            const price = getPriceForProductCode(product_code);
            const total = price * quantity;
            res.json({total});
        } else {
            res.json({error: "missing fields"});
        }
    } catch {
        res.json({error: "invalid input"});
    }
});

app.listen(5000, () => console.log('Server on 5000'));
