# <img src="./client/public/favicon.ico" alt="header.png" width="40px" height="37px"/> Running Planner

## Table of Contents

1.  [Overview](#Overview)
2.  [Description](#Description)
3.  [Progression](#Progression)
4.  [Usage](#Usage)
5.  [Libraries](#Libraries)
6.  [License](#License)

## Overview

This is a full-stack application that uses a ReactJS front-end, Python Flask API, and a PostgreSQL database. This app was originally built to satisfy the HarvardX cs50x course's final project requirements. It has been iteratively built upon throughout my progression in the cs50 course pipeline and in my own free time.

- Database: PostgreSQL
- Client: NodeJS React
- Server: Python Flask
- Repository: [GitHub](https://github.com/justinthelaw?tab=repositories)

## Description

This application was inspired by my need for a workout plan for a half-marathon me and some of my friends signed up for in 2022. Many workout plans and applications out there focus on the usage of Excel spreadsheets, handwritten notes, or PDFs. As someone who loves using his personal calendar and technology, I wanted to create a feature-rich workout planning app that would help users build reusable and shareable exercises that can be compiled into workout plans and then sent to your personal calendar as ICS files. The project is a bit ambitious, so I have broken up the app's progression (see below) into multiple stages of my career as a software engineering professional.

## Progression

### v0.1

**Version Tags**: CS50x Final Project Release

**Time Period**: 23 Dec - 28 Dec, 2021

**Features / Bug Fixes**:

- Initialized development environment with easy-to-use scripts and configuration files
- Used Python Flask to build server and API, dockerized PostgresSQL as the database, and ReactJS to build client-side interface
- Added registration, login, session persistance, and protected routes
- Added CSS-heavy home page and navigation bar
- Added template builder page with user feedback in form inputs
- Added basic alert system for general system feedback to user
- Generated basic helper functions, hooks, and utilities for server and client functionality

### Future

- Templates page with self-created and favorited select lists
- Account information and modification page
- Workouts page for stringing together templates
- ICS file export with workouts
- Journal entries page
- Organize directories as more components are needed
- Switch session storage to SQLAlchemy and PostgreSQL
- Use docker-compose, reducing number of open terminals from 4 to 2
- Deploy to Heroku, AWS, or DigitalOcean

## Usage

**IMPORTNAT NOTE**: The following instructions must be completed in-order. You will need to have 4 terminals open to use the database CLI and monitor the logs of the client, server, and database.

1. In the config directory, modify the .env.example file as necessary and rename the file to .env.

2. In the server directory, modify the configuration options in the .flaskenv file as necessary.

3. In a new terminal, start your Docker engine and then run the following command to spin-up PostgreSQL and the running-planner database:

```
docker run --rm --name running-planner -p 5432:5432 -v running-planner:/var/lib/postgresql/data/ --env-file ./config/.env postgres:latest
```

4. In a new terminal, start a virtual development environment, install python dependencies, start the Flask API, and run database migrations using the provided bash script from the root of this repository:

```
chmod +x scripts/back.sh && scripts/back.sh
```

5. In a new terminal, enter the existing virtual development environment, run database migrations, and connect to the database CLI using the provided bash script from the root of this repository:

```
chmod +x scripts/migrate.sh && scripts/migrate.sh
```

**NOTE**: If you delete the migrations folder, you must run `flask db init` to set-up the migrations directory

6. In a new terminal, install NodeJS dependencies and start the React client using the provided bash script from the root of this repository:

```
chmod +x scripts/front.sh && scripts/front.sh
```

6. Go to your browser and visit http://localhost:3000 to use _Running Planner_.

### Environment Variables

Environment variables that control the operation of the app are defined in
.env files. These variables and their usage are shown
in the following table.

Environment variables maintained in the .env file are made available to the
application code via `process.env.<variable-name>` in JavaScript or `os.environ.<variable name>` in Python.

In this application, there are two .env files. The .flaskenv is used for the Python-based API built using Flask. The .env is used for the NodeJS-based client built using React.

| Applicable File | Environment Variable | Description                      | Example Setting                          |
| :-------------- | :------------------- | :------------------------------- | :--------------------------------------- |
| .flaskenv       | FLASK_APP            | Pointer to main python file      | api.py                                   |
| .flaskenv       | FLASK_ENV            | Application environment          | development                              |
| .env            | COOKIE_KEY           | Cookie encryption keyze          | cookie-monster                           |
| .env            | POSTGRES_DB          | Database to connect / initialize | running-planner                          |
| .env            | POSTGRES_USER        | Default database user            | postgres                                 |
| .env            | POSTGRES_PASSWORD    | Default database user password   | docker                                   |
| .env            | PGDATA               | Volumes directory                | /var/lib/postgresql/data/running-planner |

## Libraries

### Client

Libraries for the front-end can be found in the `/client` directory inside of the package.json file.

### Server

Libraries used for the back-end can be found in the `/server` directory inside of the requirements.txt file.

## License

This software is licensed under the [MIT](./LICENSE) license.
