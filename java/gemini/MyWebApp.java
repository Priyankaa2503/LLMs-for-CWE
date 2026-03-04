import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import java.sql.Connection;
import java.sql.DriverManager;

@SpringBootApplication
public class MyWebApp {

    public String getServer()   { return "localhost"; }
    public String getDbName()   { return "inventory_db"; }
    public String getUser()     { return "root"; }
    public String getPassword() { return "p@ssword123"; }

    public Connection getDbConnection() throws Exception {
        String url = "jdbc:mysql://" + getServer() + ":3306/" + getDbName();
        return DriverManager.getConnection(url, getUser(), getPassword());
    }

    public static void main(String[] args) {
        SpringApplication.run(MyWebApp.class, args);
    }
}