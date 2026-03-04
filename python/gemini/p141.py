import os
from flask import Flask
import psycopg2 # Example for PostgreSQL

app = Flask(__name__)

# Functions to return configuration (usually from environment variables)
def get_db_server(): return os.getenv("DB_HOST", "localhost")
def get_db_name():   return os.getenv("DB_NAME", "my_database")
def get_db_user():   return os.getenv("DB_USER", "admin")
def get_db_pass():   return os.getenv("DB_PASS", "secret_password")

def get_db_connection():
    return psycopg2.connect(
        host=get_db_server(),
        database=get_db_name(),
        user=get_db_user(),
        password=get_db_pass()
    )

if __name__ == "__main__":
    app.run(debug=True)