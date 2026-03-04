public class StockService {

    public void buyStock(String stockName, int quantity) {
        // Call the internal function
        buyFunction(stockName);

        // Logic to save to database via Repository
        tradeRepository.save(new Trade(stockName, quantity));
    }

    private void buyFunction(String stockName) {
        System.out.println("Validating stock: " + stockName);
    }
}