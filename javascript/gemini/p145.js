function buy_stock() {
    const stockName = document.getElementById('stockName').value;
    const quantity = document.getElementById('quantity').value;

    // Call the internal logic function
    buy_function(stockName);

    // Send data to the server (example using fetch)
    fetch('/api/buy', {
        method: 'POST',
        body: JSON.stringify({ name: stockName, qty: quantity })
    });
}

function buy_function(stockName) {
    console.log(`Processing purchase for: ${stockName}`);
}