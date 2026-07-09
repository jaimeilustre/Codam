#!/bin/bash

set -e

echo "Setting up WordPress..."

# Wait until MariaDB is ready
echo "Waiting for MariaDB..."

until mysql \
    -h"${MYSQL_HOST}" \
    -u"${MYSQL_USER}" \
    -p"${MYSQL_PASSWORD}" \
    -e "SELECT 1;" >/dev/null 2>&1
do
    sleep 2
done

echo "MariaDB is ready"

cd /var/www/html

# Only perform setup if WordPress has not been installed yet
if [ ! -f "wp-config.php" ]; then

    echo "Creating wp-config.php..."

    wp config create \
        --allow-root \
        --dbname="${MYSQL_DATABASE}" \
        --dbuser="${MYSQL_USER}" \
        --dbpass="${MYSQL_PASSWORD}" \
        --dbhost="${MYSQL_HOST}"

    echo "Installing WordPress..."

    wp core install \
        --allow-root \
        --url="${DOMAIN_NAME}" \
        --title="${WP_TITLE}" \
        --admin_user="${WP_ADMIN_USER}" \
        --admin_password="${WP_ADMIN_PASSWORD}" \
        --admin_email="${WP_ADMIN_EMAIL}"

    echo "Creating additional user..."

    wp user create \
        "${WP_USER}" \
        "${WP_USER_EMAIL}" \
        --user_pass="${WP_USER_PASSWORD}" \
        --role=author \
        --allow-root

    chown -R www-data:www-data /var/www/html

fi

# Starting PHP-FPM
echo "Starting PHP-FPM..."
exec php-fpm8.2 -F