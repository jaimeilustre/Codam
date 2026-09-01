# Inception — Developer Documentation

This document explains how to set up, build, and manage the Inception project from a developer's perspective.

## 1. Prerequisites

Before working on this project, make sure you have:

- A Linux Virtual Machine (this project must run inside a VM, not directly on a host OS).
- [Docker Engine](https://docs.docker.com/engine/install/) installed.
- Docker Compose (the `docker compose` plugin, included with recent Docker installations).
- `make` installed (usually pre-installed on Debian/Ubuntu-based systems).
- `sudo` privileges, required for creating data directories under `/home/<login>/data` and for cleaning them up.

Verify your setup with:

```bash
docker --version
docker compose version
make --version
```

## 2. Project structure

```
.
├── Makefile
├── secrets/
│   ├── db_password.txt
│   ├── db_root_password.txt
│   ├── wp_admin_password.txt
│   └── wp_user_password.txt
└── srcs/
    ├── .env
    ├── docker-compose.yml
    └── requirements/
        ├── mariadb/
        │   ├── Dockerfile
        │   ├── conf/
        │   │   └── 50-server.cnf
        │   └── tools/
        │       └── mariadb_setup.sh
        ├── wordpress/
        │   ├── Dockerfile
        │   ├── conf/
        │   │   └── www.conf
        │   └── tools/
        │       └── wordpress_setup.sh
        └── nginx/
            ├── Dockerfile
            ├── conf/
            │   └── nginx.conf
            └── tools/
                └── nginx_setup.sh
```

## 3. Configuration files and secrets

### 3.1 Environment variables (`srcs/.env`)

All non-sensitive configuration values (domain name, database name, usernames, WordPress titles/emails, etc.) live in `srcs/.env`. This file is read by `docker-compose.yml` and passed into each container via the `environment:` block.

Example content:

```env
DOMAIN_NAME=<login>.42.fr

# MariaDB
MYSQL_DATABASE=wordpress
MYSQL_USER=wpuser
MYSQL_HOST=mariadb
MYSQL_PORT=3306

# WordPress
WP_TITLE=Inception
WP_ADMIN_USER=<non-admin-like-username>
WP_ADMIN_EMAIL=admin@example.com
WP_USER=user
WP_USER_EMAIL=user@example.com
```

**Note:** the WordPress admin username must not contain `admin`/`Admin`/`administrator`/`Administrator` in any form.

### 3.2 Secrets (`secrets/`)

Actual passwords are never stored in `.env`, in the Dockerfiles, or in Git. They live as plain text files under `secrets/` at the repository root, and are mounted into containers as Docker secrets (available at `/run/secrets/<name>` inside each container):

| File | Used by |
|---|---|
| `db_root_password.txt` | MariaDB root password |
| `db_password.txt` | MariaDB application user password (shared with WordPress) |
| `wp_admin_password.txt` | WordPress administrator account password |
| `wp_user_password.txt` | WordPress secondary (author) account password |

These files are excluded from version control via `.gitignore`. Create them yourself before first build, e.g.:

```bash
mkdir -p secrets
echo "your-root-password"  > secrets/db_root_password.txt
echo "your-db-password"    > secrets/db_password.txt
echo "your-admin-password" > secrets/wp_admin_password.txt
echo "your-user-password"  > secrets/wp_user_password.txt
```

### 3.3 Domain resolution

Since `<login>.42.fr` isn't a real, publicly resolvable domain, add an entry to `/etc/hosts` on the machine you'll browse from, pointing it at the VM's IP:

```
127.0.0.1   <login>.42.fr
```

(Use the VM's actual IP instead of `127.0.0.1` if browsing from outside the VM.)

## 4. Building and launching the project

The `Makefile` at the repository root drives the whole build/launch process.

| Target | What it does |
|---|---|
| `make` / `make all` | Creates host data directories, builds all Docker images, and starts all containers |
| `make build` | Creates host data directories and builds the images only |
| `make up` | Starts the containers (builds first if needed) |
| `make down` | Stops and removes the containers |
| `make clean` | Stops containers and prunes unused Docker images/system data |
| `make fclean` | Runs `clean`, removes named volumes, and deletes the host data directories |
| `make re` | Full teardown (`fclean`) followed by a full rebuild (`all`) |

Typical first-time setup:

```bash
make all
```

Typical full reset (useful when debugging or testing from a clean state):

```bash
make re
```

## 5. Managing containers and volumes

### 5.1 Containers

```bash
docker compose -f srcs/docker-compose.yml ps          # list running containers
docker logs mariadb                                    # view a service's logs
docker logs wordpress
docker logs nginx
docker exec -it mariadb bash                            # shell into a container
docker exec -it wordpress wp user list --allow-root --path=/var/www/html   # inspect WP users
```

Every service is configured with `restart: unless-stopped`, so containers automatically recover from a crash:

```bash
docker kill mariadb        # simulate a crash
docker compose -f srcs/docker-compose.yml ps   # confirm it restarts on its own
```

### 5.2 Rebuilding after a change

Whenever a Dockerfile, config file, or setup script is modified, rebuild that service before restarting, to make sure the change is actually picked up:

```bash
docker compose -f srcs/docker-compose.yml build --no-cache <service-name>
docker compose -f srcs/docker-compose.yml up -d
```

`--no-cache` is recommended when troubleshooting, to eliminate any risk of a stale cached layer masking a fix.

### 5.3 Volumes

Two named Docker volumes are used for persistent storage, both configured with the `local` driver and `bind` mount options so their data physically lives on the host filesystem (required by the subject), while still being managed by Docker as proper named volumes:

```bash
docker volume ls
docker volume inspect srcs_mariadb_data
docker volume inspect srcs_wordpress_data
```

Their actual data lives at:

```
/home/<login>/data/mariadb      # MariaDB data directory
/home/<login>/data/wordpress    # WordPress files
```

Because this data is stored on the host, it survives `docker compose down` and container/image rebuilds — it is only removed by `make fclean` (or a manual `sudo rm -rf /home/<login>/data`).

## 6. Notes on initialization logic

Both the MariaDB and WordPress setup scripts are idempotent: they check for a marker of prior initialization (a sentinel file for MariaDB, the presence of `wp-config.php` for WordPress) before running their first-time setup steps. This means restarting the containers without wiping the volumes will **not** re-run installation — data and configuration persist as expected. This is deliberate and important to understand when debugging: if a container appears to "skip" setup unexpectedly, check whether the corresponding host data directory already contains data from a previous run.
