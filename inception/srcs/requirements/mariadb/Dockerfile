FROM debian:bookworm

RUN apt-get update && \
    apt-get install -y --no-install-recommends mariadb-server && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir -p /run/mysqld && \
    chown -R mysql:mysql /run/mysqld /var/lib/mysql

COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf
COPY tools/mariadb_setup.sh /usr/local/bin/mariadb_setup.sh

RUN chmod +x /usr/local/bin/mariadb_setup.sh

EXPOSE 3306

ENTRYPOINT ["mariadb_setup.sh"]