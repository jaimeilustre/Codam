#!/bin/bash

# Exit script if any of the command fails
set -e

echo "MariaDB initialization is starting..."

MYSQL_ROOT_PASSWORD=$(cat /run/secrets/db_root_password)
MYSQL_PASSWORD=$(cat /run/secrets/db_password)

# Initialize MySQL data directory if it doesn't exist
if [ ! -d "/var/lib/mysql/mysql" ]; then

    echo "Initializing database directory..."

    mysql_install_db \
        --user=mysql \
        --datadir=/var/lib/mysql \
        > /dev/null

    # Starting the server
    echo "Starting temporary MariaDB server for setup..."

    mysqld \
        --skip-networking \
        --socket=/run/mysqld/mysqld.sock \
        --user=mysql & 

    pid="$!"

    # Wait for MariaDB to be ready
    echo "Waiting for MariaDB..."

    until mysqladmin \
        --socket=/run/mysqld/mysqld.sock \
        ping >/dev/null 2>&1
    do
        sleep 1
    done

    echo "MariaDB is ready!"

    # Setup database and users for SQL
    echo "Setting up SQL..."

    mysql \
        --socket=/run/mysqld/mysqld.sock \
        -u root << EOF
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';
FLUSH PRIVILEGES;
EOF

    # Shutting down temporary server
    echo "Shutting down temporary MariaDB..."

    mysqladmin \
        --socket=/run/mysqld/mysqld.sock \
        -u root \
        -p"${MYSQL_ROOT_PASSWORD}" \
        shutdown

    wait "$pid" || true

else

    echo "MariaDB data directory already exists."
    echo "Skipping database initialization."

fi

# Start MariaDB
echo "Setup complete. Starting MariaDB..."

exec mysqld \
    --user=mysql \
    --datadir=/var/lib/mysql \
    --socket=/run/mysqld/mysqld.sock