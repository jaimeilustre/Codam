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

### Architecture

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

## Resources

https://docs.docker.com/reference/dockerfile/#env
https://docs.docker.com/compose/
https://github.com/WCSCourses/index/blob/main/Docker_guide.md
