FROM debian:bookworm

# Installing MariaDB
RUN apt-get update && \
    apt-get install -y mariadb-server && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir -p /run/mysqld && \
    chown mysql:mysql /run/mysqld

# Copy configuration
COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d
COPY tools/mariadb_setup.sh /usr/local/bin

EXPOSE 3306

# Set permissions for initialization script
RUN chmod +x /usr/local/bin/mariadb_setup.sh

ENTRYPOINT ["mariadb_setup.sh"]