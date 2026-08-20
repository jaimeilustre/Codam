FROM debian:bookworm

# Installing all the necessary packages for Wordpress
RUN apt-get update && \
    apt-get install -y \
    php-fpm \
    php-mysql \
    php-curl \
    php-gd \
    php-intl \
    php-mbstring \
    php-xml \
    php-zip \
    curl \
    tar \
    mariadb-client \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Installing WP-CLI
RUN curl -O  https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && chmod +x wp-cli.phar \
    && mv wp-cli.phar /usr/local/bin/wp

# Installing WordPress
RUN mkdir -p /var/www/html \
    && curl -O https://wordpress.org/latest.tar.gz \
    && tar -xzf latest.tar.gz \
    && mv wordpress/* /var/www/html \
    && rm -rf wordpress latest.tar.gz

# Copy configuration file
COPY conf/www.conf /etc/php/8.2/fpm/pool.d

# Copy setup script
COPY tools/wordpress_setup.sh /usr/local/bin

# Set permissions for initialization script
RUN chmod +x /usr/local/bin/wordpress_setup.sh

# Which port the container's application INTENDS to use
EXPOSE 9000

# Set permissions for initialization script
RUN chmod +x /usr/local/bin/wordpress_setup.sh

# Defines the command that runs when you start a container
ENTRYPOINT ["wordpress_setup.sh"]