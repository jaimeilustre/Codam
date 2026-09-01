*This project has been created as part of the 42 curriculum by jilustre.*

# Inception

## Description

Inception is a system administration project centered around containerization using Docker. The objective is to build a complete web infrastructure from individual Docker containers without relying on pre-built application images. Each service is built from a custom Dockerfile based on Debian, configured manually, and orchestrated using Docker Compose.

The infrastructure consists of three main services:
- NGINX acting as a reverse proxy with TLS enabled.
- WordPress running with PHP-FPM.
- MariaDB providing persistent database storage for WordPress.

The services communicate through a dedicated Docker network while persistent data is stored using Docker volumes. The entire infrastructure is managed using Docker Compose, making it reproducible, portable, and easy to deploy.

## Project Description

### Why Docker? 

Docker provides lightweight, isolated environments that package an application together with its dependencies. Unlike traditional virtual machines, containers share the host operating system's kernel, making them significantly faster to start and more resource efficient.

For this project, Docker makes it possible to separate each service into its own container while ensuring that the complete infrastructure can be reproduced consistently on any machine.

The project also requires building custom images from Debian instead of using official application images. This provides a better understanding of how each service is installed, configured, and initialised before becoming part of the final infrastructure.

### Sources included

#### NGINX

NGINX acts as the public entry point of the infrastructure. It terminates TLS connections, serves static content, and forwards PHP requests to the WordPress container through PHP-FPM. Only this container exposes ports to the host machine.

#### WordPress

The WordPress container hosts the web application and executes PHP code using PHP-FPM. It communicates with the MariaDB container to retrieve and store website content while remaining isolated from direct external access.

#### MariaDB

MariaDB provides persistent relational database storage for WordPress. During its first startup, the container initialises the database, creates the required users, and configures the WordPress database before launching the database server.

### Design choices

The implementation follows several Docker best practices:

- Every service is built from a custom Debian-based Docker image.
- Each container has a single responsibility.
- Containers communicate through a dedicated Docker bridge network.
- Only NGINX is accessible from outside the Docker network.
- Persistent data is stored in Docker-managed volumes.
- Service initialization is automated through startup scripts, avoiding manual configuration after deployment.

### Comparisons

#### Virtual Machines vs Docker

Both virtual machines and Docker containers provide isolated execution environments. The primary difference is that virtual machines virtualize an entire operating system, whereas Docker containers share the host operating system's kernel.

As a result, containers require fewer resources, start significantly faster, and are easier to rebuild or replace. This makes Docker particularly well suited for infrastructures composed of multiple independent services such as NGINX, WordPress, and MariaDB.

#### Secrets vs Environment Variables

Environment variables provide runtime configuration such as database names, usernames, ports, or hostnames. They are simple to configure but are not intended to securely store confidential information.

Docker Secrets are specifically designed for sensitive data such as passwords, certificates, or API keys. Unlike environment variables, secrets are not embedded into the container image and are only made available to containers that require them.

This project primarily uses environment variables to configure services, while Docker Secrets represent the preferred approach for production deployments where sensitive credentials require stronger protection.

#### Docker Network vs Host Network

Docker's bridge network allows containers to communicate privately using their service names while remaining isolated from the host machine. This prevents unnecessary exposure of internal services.

Host networking removes this isolation by allowing containers to share the host's network stack directly. Although this can reduce networking overhead, it also removes network isolation and increases the likelihood of port conflicts.

This project uses Docker's bridge network so that only the NGINX container is publicly accessible while WordPress and MariaDB remain internal services.

#### Docker Volumes vs Bind Mounts

Docker volumes provide persistent storage that is managed independently of individual containers. They are particularly suitable for application data that must survive container recreation, such as databases and uploaded files.

Bind mounts directly map files or directories from the host system into a container. They are commonly used during development because changes made on the host are immediately reflected inside the container.

This project uses Docker volumes to persist the MariaDB database and WordPress data, ensuring that rebuilding or replacing containers does not result in data loss while keeping the application independent of the host filesystem.

## Instructions

### 1. Starting the Project

Make sure Docker and Docker Compose are installed and that the project has been configured correctly.

From the project root, run:

```bash
make
```

This builds and starts the Docker containers using the project's Docker Compose configuration.

To only start the containers:

```bash
make up
```

## 2. Stopping the Project

To stop and remove the containers:

```bash
make down
```

To stop containers and prune unused Docker images/system data:

```bash
make clean
```

Stopping or removing the containers does not remove the persistent project data stored in the Docker volumes.

To stop and remove the containers, but also remove the named volumes and delete the host data directories:

```bash
make fclean
```

For a full teardown followed by a full rebuild:

```bash
make re
```

## 3. Accessing the Website

Once the containers are running, the WordPress website can be accessed through:

```text
https://<domain_name>
```

In this case, since it has to be our intra login, the corresponding domain for this project would be:

```text
https://jilustre.42.fr
```

The project uses HTTPS, so the browser may display a certificate warning if a self-signed certificate is being used. Do not be alarmed, this is expected for the development environment.

## 4. Accessing the Administration Panel

The WordPress administration panel is available at:

```text
https://jilustre.42.fr/wp-admin
```

Log in using the WordPress administrator credentials configured for the project (more details about this in the next section).

## 5. Credentials

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

The secret files should NOT be committed to Git.

The WordPress administrator credentials are configured through the project's environment configuration and should be treated as sensitive information.

## 6. Checking the Services

To check whether the containers are running:

```bash
docker compose -f srcs/docker-compose.yml ps
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
docker logs mariadb
docker logs wordpress
docker logs nginx
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

### Checking TLS

As mentioned before, when testing wordpress we have to go on the browser and type the domain name specified. Alternatively, we can check through the terminal using curl:

```bash
curl -k https://jilustre.42.fr # -k skips the certification validation since we're using a self signed one
```

With this in mind, we can check if using just http we can access the website; THIS SHOULD NOT WORK:

```bash
curl http://jilustre.42.fr
```

We also should make sure that we are running only TLSv1.2 or TLSv1.3:

```bash
openssl s_client -connect jilustre.42.fr:443 -tls1_1	# should fail
openssl s_client -connect jilustre.42.fr:443 -tls1_2	# should work
```

### Checking the MariaDB container

To enter the container:

```bash
docker exec -it mariadb bash
```

Then:

```bash
mysql --protocol=socket --socket=/run/mysqld/mysqld.sock -u root -p
```

Type the root password and run the following commands:

```text
SHOW DATABASES;
SELECT User, Host FROM mysql.user;
```

You will see the wordpress_db listed among the databases and the wp_user present.

### Checking the Wordpress container

```bash
docker compose -f srcs/docker-compose.yml exec wordpress bash
```

Then:

```bash
cd /var/www/html
wp core is-installed --allow-root
```

We can also inspect the Wordpress users:

```bash
docker exec -it wordpress wp user list --allow-root --path=/var/www/html
```

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
docker volume inspect <volume_name>
```

We should expect to see that "Mountpoint/device" shows home/$USER/data/mariadb and home/$USER/data/wordpress.

We can also check the directories themselves:

```bash
ls -la /home/$USER/data/mariadb
ls -la /home/$USER/data/wordpress
```

We should see the database files and Wordpress files.

## 7. Persistent Data

The project uses persistent volumes so that removing and recreating containers does not automatically remove the WordPress website or MariaDB database.

The persistent data is stored on the host in:

```text
/home/<user>/data/mariadb
/home/<user>/data/wordpress
```

The MariaDB directory contains the database files while the WordPress directory contains the WordPress files.

Do not manually delete these directories unless you intend to permanently remove the stored data.

## 8. Troubleshooting

If the website cannot be accessed, first check the container status:

```bash
docker compose -f srcs/docker-compose.yml ps
```

Then check the logs:

```bash
docker logs -f <container_name>
```

If MariaDB is not running, WordPress will not be able to connect to the database.

If WordPress is not running, NGINX will not be able to forward PHP requests correctly.

If NGINX is not running, the website will not be accessible through HTTPS.

## Resources

https://docs.docker.com/reference/dockerfile/#env
https://docs.docker.com/compose/
https://github.com/WCSCourses/index/blob/main/Docker_guide.md
https://www.docker.com/resources/cli-cheat-sheet/

https://nginx.org/en/linux_packages.html
https://nginx.org/en/docs/example.html
https://www.solo.io/topics/nginx/nginx-configuration

https://www.thomas-krenn.com/en/wiki/Installation_and_configuration_of_MariaDB
https://mariadb.com/docs/server/mariadb-quickstart-guides/installing-mariadb-server-guide
https://opensource.com/article/20/10/mariadb-mysql-linux

https://ubuntu.com/tutorials/install-and-configure-wordpress#1-overview
https://developer.wordpress.org/advanced-administration/before-install/howto-install/
https://www.cherryservers.com/blog/install-wordpress-on-ubuntu-2404

## AI Usage

AI was used throughout the project as a learning and clarification tool. I used it to better understand concepts related to Docker, Docker Compose, networking, volumes, environment variables, secrets, MariaDB, WordPress, PHP-FPM, and NGINX. When I encountered unclear or confusing parts of the project guides and documentation, I used AI to help clarify what they meant and why certain approaches were being used. AI was also occasionally used to provide examples or alternative implementations to help me understand how a particular component could be configured. The final implementation, configuration, and decisions were reviewed and adapted by me to fit the requirements of the project.
