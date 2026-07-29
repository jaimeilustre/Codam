FROM debian:bookworm

# Installing NGINX and OpenSSL
RUN apt-get update && \
    apt-get install -y \
    nginx \
    openssl \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Create SSL directory
RUN mkdir -p /etc/nginx/ssl

# Copy NGINX configuration
COPY conf/nginx.conf /etc/nginx/conf.d/default.conf

# Copy setup script
COPY tools/nginx_setup.sh /usr/local/bin

EXPOSE 443

# Set permissions for initialization script
RUN chmod +x /usr/local/bin/nginx_setup.sh

ENTRYPOINT ["nginx_setup.sh"]