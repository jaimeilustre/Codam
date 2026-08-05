#!/bin/bash

set -e

echo "Setting up NGINX..."

openssl req \
    -x509 \
    -nodes \
    -days 365 \
    -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/inception.key \
    -out /etc/nginx/ssl/inception.crt \
    -subj "/C=NL/ST=Noord-Holland/L=Amsterdam/O=42/CN=${DOMAIN_NAME}"

chmod 600 /etc/nginx/ssl/inception.key
chmod 644 /etc/nginx/ssl/inception.crt

echo "Setup complete. Starting NGINX..."

exec nginx -g "daemon off;"