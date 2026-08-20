FROM debian:bookworm

# Installing MariaDB
RUN apt-get update && \
    apt-get install -y --no-install-recommends mariadb-server && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Setups the socket directory and makes it writable by the user
RUN mkdir -p /run/mysqld && \
    chown -R mysql:mysql /run/mysqld /var/lib/mysql

# Copy configuration file
COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf

# Copy setup script
COPY tools/mariadb_setup.sh /usr/local/bin/mariadb_setup.sh

# Setup permissions for script to execute
RUN chmod +x /usr/local/bin/mariadb_setup.sh

# Which port the container's application INTENDS to use
EXPOSE 3306

# Defines the command that runs when you start a container
ENTRYPOINT ["mariadb_setup.sh"]