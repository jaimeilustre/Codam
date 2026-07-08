FROM debian:bookworm

# Installing Wordpress
RUN apt-get update && \
    apt-get install -y \
    php-fpm \
    php-mysql \
    php-curl \
    curl \
    mariadb-client \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir -p /run/mysqld && \
    chown mysql:mysql /run/mysqld

# Create WordPress directory
WORKDIR /var/www/html

# Copy PHP-FPM configuration
COPY conf/www.conf /etc/php/8.2/fpm/pool.d

COPY tools/wordpress_setup.sh /usr/local/bin

EXPOSE 9000

# Set permissions for initialization script
RUN chmod +x /usr/local/bin/wordpress_setup.sh

ENTRYPOINT ["wordpress_setup.sh"]