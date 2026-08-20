#!/bin/bash

set -e

echo "[wordpress] Setting up WordPress..."

MYSQL_PASSWORD=$(cat /run/secrets/db_password)
WP_USER_PASSWORD=$(cat /run/secrets/wp_user_password)
WP_ADMIN_PASSWORD=$(cat /run/secrets/wp_admin_password)

# Wait until MariaDB is ready
echo "[wordpress] Waiting for MariaDB..."

until mysql \
    -h"${MYSQL_HOST}" \
    -P 3306 \
    -u"${MYSQL_USER}" \
    -p"${MYSQL_PASSWORD}" \
    -e "SELECT 1;" >/dev/null 2>&1
do
    sleep 2
done

echo "[wordpress] MariaDB is ready!"

cd /var/www/html

# Only perform setup if WordPress has not been installed yet
if [ ! -f "wp-config.php" ]; then

    echo "[wordpress] Creating wp-config.php..."

    wp config create \
        --allow-root \
        --dbname="${MYSQL_DATABASE}" \
        --dbuser="${MYSQL_USER}" \
        --dbpass="${MYSQL_PASSWORD}" \
        --dbhost="${MYSQL_HOST}"

    echo "[wordpress] Installing WordPress core..."

    wp core install \
        --allow-root \
        --url="${DOMAIN_NAME}" \
        --title="${WP_TITLE}" \
        --admin_user="${WP_ADMIN_USER}" \
        --admin_password="${WP_ADMIN_PASSWORD}" \
        --admin_email="${WP_ADMIN_EMAIL}"

    echo "[wordpress] Creating additional user (${WP_USER})..."

    wp user create \
        "${WP_USER}" \
        "${WP_USER_EMAIL}" \
        --user_pass="${WP_USER_PASSWORD}" \
        --role=author \
        --allow-root

    chown -R www-data:www-data /var/www/html

    echo "[wordpress] Wordpress installation complete!"
else

    echo "[wordpress] wp-config.php already exists - skipping Wordpress initialization."

fi

# Starting PHP-FPM
echo "Starting PHP-FPM in the foreground..."
exec php-fpm8.2 -F