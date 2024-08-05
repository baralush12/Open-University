# Running the Application
## This guide explains how to run the Spring Boot backend with Docker Compose and serve the Angular frontend manually.

### Prerequisites
Before you begin, ensure you have the following installed on your machine:

- Docker
- docker-compose
- Java Development Kit (JDK) version 17 or higher
- Apache Maven
- Node.js and npm
- Running the Spring Boot Application with Docker Compose


***Run***

`cd Bookify/backend`

`docker-compose up --build`

***first time running this command it will take some time (3-5 minutes).**


`cd Bookify\frontend\book-store\src`

`npm install`

`ng serve --open`

The Angular application will be served locally and automatically open in your default web browser at http://localhost:4200.

**Accessing the Application**

Once both the Spring Boot backend and Angular frontend are running, you can access the full application by navigating to http://localhost:4200 in your web browser.