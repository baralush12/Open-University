# Use the official MySQL image from the Docker Hub
FROM mysql:latest

# Set environment variables for MySQL root user
ENV MYSQL_ROOT_PASSWORD=root
ENV MYSQL_DATABASE=bookstore

# Copy the initialization script to the Docker entrypoint directory
COPY init_db.sql /docker-entrypoint-initdb.d/

# Expose the default MySQL port
EXPOSE 3306
