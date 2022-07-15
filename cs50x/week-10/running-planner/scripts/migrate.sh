printf "=> Setting up virtual environment...\n";
cd server && source venv/bin/activate;

printf "=> Initializing and running migrations...\n";
flask db migrate && flask db upgrade;

printf "\n=> Opening docker container bash...\n";
docker exec -it running-planner bash;