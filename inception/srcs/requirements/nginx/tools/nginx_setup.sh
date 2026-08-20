#!/bin/bash

set -e

echo "[nginx] Setting up NGINX..."

# Generate a self signed SSL certificate
openssl req \
    -x509 \
    -nodes \
    -days 365 \
    -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/inception.key \
    -out /etc/nginx/ssl/inception.crt \
    -subj "/C=NL/ST=Noord-Holland/L=Amsterdam/O=42/CN=${DOMAIN_NAME}"

# Protect the private key
chmod 600 /etc/nginx/ssl/inception.key

# Make the certificate readable
chmod 644 /etc/nginx/ssl/inception.crt

echo "[nginx] SSL certificate generated, starting NGINX..."

# Keep NGINX running in the background
exec nginx -g "daemon off;"