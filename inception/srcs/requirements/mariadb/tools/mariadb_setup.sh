#!/bin/bash

# Exit script if any of the command fails
set -euo pipefail

echo "[mariadb] Starting MariaDB container entrypoint..."

MYSQL_ROOT_PASSWORD="$(cat /run/secrets/db_root_password)"
MYSQL_PASSWORD="$(cat /run/secrets/db_password)"

: "${MYSQL_DATABASE:?MYSQL_DATABASE is not set}"
: "${MYSQL_USER:?MYSQL_USER is not set}"

DATADIR="/var/lib/mysql"
SOCKET="/run/mysqld/mysqld.sock"
INIT_MARKER="${DATADIR}/.setup_complete"

# Initialize MySQL data directory if it doesn't exist
if [ ! -f "$INIT_MARKER" ]; then

    echo "[mariadb] First run detected (no init marker found)."
    echo "[mariadb] Initializing data directory at ${DATADIR}..."

    mysql_install_db \
        --user=mysql \
        --datadir="$DATADIR" \
        > /dev/null

    # Starting the server
    echo "[mariadb] Starting temporary MariaDB instance (socket-only, no network) for setup..."

    mysqld \
        --skip-networking \
        --socket="$SOCKET" \
        --datadir="$DATADIR" \
        --user=mysql & 

    TEMP_PID="$!"

    # Wait for MariaDB to be ready
    echo "[mariadb] Waiting for temporary instance to accept connections..."

    for i in $(seq 1 30); do
        if mysqladmin \
            --protocol=socket \
            --socket=${SOCKET} \
            ping >/dev/null 2>&1; then
            break
        fi
        sleep 1
    done

    if ! mysqladmin \
            --protocol=socket \
            --socket=${SOCKET} \
            ping >/dev/null 2>&1; then
            echo "ERROR: temporary instance did not become ready within 30 seconds." >&2
            exit 1
    fi

    # Setup database and users for SQL
    echo "[mariadb] Temporary instance is up. Creating database, user and setting root password..."

    mysql \
        --protocol=socket \
        --socket=${SOCKET} \
        -u root <<-SQL
    ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
    CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;
    CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
    GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';
    FLUSH PRIVILEGES;
SQL

    # Shutting down temporary server
    echo "[mariadb] Database and user created. Shutting down temporary instance..."

    mysqladmin \
        --protocol=socket \
        --socket=${SOCKET} \
        -u root \
        -p"${MYSQL_ROOT_PASSWORD}" \
        shutdown

    wait "$TEMP_PID" 2>/dev/null || true

    touch "$INIT_MARKER"
    echo "[mariadb] First time setup complete! Marker written to ${INIT_MARKER}."

else
    echo "[mariadb] Init marker found at ${INIT_MARKER}, skipping setup."
fi

# Start MariaDB
echo "[mariadb] Setup complete. Launching MariaDB in the foreground..."

exec mysqld \
    --user=mysql \
    --datadir="$DATADIR" \
    --socket="$SOCKET"