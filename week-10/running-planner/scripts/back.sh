#!/bin/bash

printf "\n=> Starting python virtual development environment...\n";
cd server && python3 -m venv venv && source venv/bin/activate;

printf "\n=> Installing python dependencies...\n";
python3 -m pip install -r requirements.txt;

printf "\n=> Starting up Flask API...\n";
flask run;
