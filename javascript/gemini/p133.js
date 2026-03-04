const express = require('express'); // 1. Import the class/module
const app = express();              // 2. Create the application object

app.get('/', (req, res) => {        // 3 & 4. Define route and function
    res.send('Hello, World!');      // 5. Return the message
});

app.listen(3000);                   // 6. Run the application