FROM debian::bookworm

# Installing MariaDB
RUN apt-get update && \
    apt-get install -y mariadb-server && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Copy configuration
COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d
COPY tool/init_db.sh /usr/local/bin

# Environment variables defaults (for testing since docker compose file hasn't been created yet)
# REMOVE BEFORE SUBMITTING!!!
ENV DB_ROOT_PASSWORD=root \
    DB_DATABASE=mariadb \
    DB_USER=user \
    DB_PASSWORD=password 

EXPOSE 3306

# Set permissions for initialization script
RUN chmod +x /usr/local/bin/init_db.sh
ENTRYPOINT ["init_db.sh"]