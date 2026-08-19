# Inception — User Documentation

## 1. Overview

This project provides a small web stack running inside Docker containers.

The stack consists of three main services:

* **NGINX** — acts as the web server and HTTPS entry point.
* **WordPress + PHP-FPM** — provides the WordPress website and processes PHP requests.
* **MariaDB** — stores the WordPress database.

The services communicate with each other through a private Docker network.

The website is exposed through NGINX using HTTPS with TLS 1.2 or TLS 1.3.

## 2. Starting the Project

Make sure Docker and Docker Compose are installed and that the project has been configured correctly.

From the project root, run:

```bash
make all
```

This builds and starts the Docker containers using the project's Docker Compose configuration.

To start the containers without rebuilding the images:

```bash
make up
```

## 3. Stopping the Project

To stop the running containers:

```bash
make down
```

To stop and remove the containers:

```bash
make clean
```

Stopping or removing the containers does not remove the persistent project data stored in the Docker volumes.

To stop and remove the containers, but also remove the unused volumes:

```bash
make fclean
```

To stopping and removing everything and rebuilding everything:

```bash
make re
```

## 4. Accessing the Website

Once the containers are running, the WordPress website can be accessed through:

```text
https://<domain_name>
```

In this case, since it has to be our intra login, the corresponding domain for this project would be:

```text
https://jilustre.42.fr
```

The project uses HTTPS, so the browser may display a certificate warning if a self-signed certificate is being used. Do not be alarmed, this is expected for the development environment.

## 5. Accessing the Administration Panel

The WordPress administration panel is available at:

```text
https://jilustre.42.fr/wp-admin
```

Log in using the WordPress administrator credentials configured for the project (more details about this in the next section).

## 6. Credentials

Sensitive credentials are not stored directly in the Docker Compose file.

Passwords are stored as Docker secrets in:

```text
secrets/
├── db_password.txt
└── db_root_password.txt
├── wp_user_password.txt
└── wp_admin_password.txt
```

Other non-secret configuration values, such as the database name, database user, domain name, and WordPress configuration, are stored in:

```text
srcs/.env
```

The secret files should not be committed to Git.

The WordPress administrator credentials are configured through the project's environment configuration and should be treated as sensitive information.

## 7. Checking the Services

To check whether the containers are running:

```bash
docker ps
```

All three services should be running:

```text
mariadb
wordpress
nginx
```

### Checking logs

To view the logs of each services:

```bash
docker compose -f srcs/docker-compose.yml logs mariadb
docker compose -f srcs/docker-compose.yml logs wordpress
docker compose -f srcs/docker-compose.yml logs nginx
```

What to expect to see:

* MariaDB successfully starting and accepting connections.
* WordPress successfully connecting to MariaDB and starting PHP-FPM.
* NGINX successfully starting and listening for HTTPS connections.

### Checking the network

To view the list of networks:

```bash
docker network ls
```

We should expect to see the network created from the compose file:

- "inception-network" or in this case: "srcs_inception-network" since it automatically adds the "srcs" when setting everything up. 

To inspect the network itself:

```bash
docker network inspect <network_name>
```

We should see that all 3 services should be listed inside the network

### Checking the volumes

To view the list of volumes:

```bash
docker volume ls
```

We should expect to see the volumes created from the compose file:

- "mariadb_data" or in this case: "srcs_mariadb_data" since it automatically adds the "srcs" when setting everything up.
- "wordpress_data" or in this case: "srcs_wordpress_data" since it automatically adds the "srcs" when setting everything up. 

To inspect the volumes themselves:

```bash

```

## 8. Persistent Data

The project uses persistent volumes so that removing and recreating containers does not automatically remove the WordPress website or MariaDB database.

The persistent data is stored on the host in:

```text
/home/<user>/data/mariadb
/home/<user>/data/wordpress
```

The MariaDB directory contains the database files.

The WordPress directory contains the WordPress website files.

Do not manually delete these directories unless you intend to permanently remove the stored data.

## 9. Troubleshooting

If the website cannot be accessed, first check the container status:

```bash
docker ps
```

Then check the logs:

```bash
docker logs -f <container_name>
```

If MariaDB is not running, WordPress will not be able to connect to the database.

If WordPress is not running, NGINX will not be able to forward PHP requests correctly.

If NGINX is not running, the website will not be accessible through HTTPS.
