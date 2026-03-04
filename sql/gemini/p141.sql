-- Define the database name
CREATE DATABASE my_database;

-- Define the database user and password
CREATE USER 'admin'@'localhost' IDENTIFIED BY 'secret_password';

-- Grant permissions (Connecting the user to the database)
GRANT ALL PRIVILEGES ON my_database.* TO 'admin'@'localhost';

-- Function-like behavior (Procedure) to return connection info
DELIMITER //
CREATE PROCEDURE GetServerInfo()
BEGIN
    SELECT @@hostname AS ServerName, DATABASE() AS DbName, CURRENT_USER() AS User;
END //
DELIMITER ;