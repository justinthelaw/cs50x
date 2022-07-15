#!/bin/bash

printf "\n=> Installing NodeJS dependencies...\n";
cd client && npm install;

printf "\n=> Starting up ReactJS client...\n";
npm start