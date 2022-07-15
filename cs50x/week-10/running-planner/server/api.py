import os

from flask import Flask, request, session
from flask_session import Session
from flask_migrate import Migrate
from werkzeug.security import check_password_hash, generate_password_hash
from dotenv import load_dotenv

from models import db, UserModel, TemplateModel
from helpers import login_required

app = Flask(__name__)

# load environment variables from ~/config/.env files
load_dotenv("../config/.env")
user = os.getenv("POSTGRES_USER")
password = os.getenv("POSTGRES_PASSWORD")
database = os.getenv("POSTGRES_DB")

# secret key for cryptographically signed cookies
app.secret_key = os.getenv("COOKIE_KEY")

# configure SQLAlchemy to point to PostgreSQL database
app.config[
    'SQLALCHEMY_DATABASE_URI'] = f"postgresql://{user}:{password}@localhost:5432/{database}"
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

# initialize application and migrations
db.init_app(app)
migrate = Migrate(app, db)

# Configure session to use signed cookies
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
app.config["PERMANENT_SESSION_LIFETIME"] = 604800  # 1 week in seconds
Session(app)


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# base API route
@app.route('/api')
def index():
    # base API route welcomes user, serves as health check
    return {"message": "Welcome to the Running Planner API!"}


# get all users
@app.route('/api/users')
@login_required
def users():
    # query all rows based on UserModel
    users = UserModel.query.all()
    # format results into JSON format
    results = [{
        "id": user.id,
        "username": user.username,
    } for user in users]
    # return count of results and result
    return {"count": len(results), "users": results}


# register new user
@app.route('/api/register', methods=["POST"])
def register():
    # check to ensure response is in JSON format
    if request.is_json:
        # extract data from request
        data = request.get_json()
        password = data["password"]
        username = data["username"]
        # check username and password validity
        if UserModel().check(username, password):
            # hash password
            hashedPassword = generate_password_hash(password)
            # check to see if username is unique
            result = UserModel.query.filter_by(username=username).first()
            if result:
                # return error message to populate alert
                return {"error": "Username already exists."}
            else:
                # add user info to database
                user = UserModel(username=username, password=hashedPassword)
                db.session.add(user)
                db.session.commit()
                # clear previous login info
                session.clear()
                # add login persistance to newly registered user
                user = UserModel.query.filter_by(username=username).first()
                session["user_id"] = user.id
                # return success message to populate alert
                return {"success": f"Welcome to Running Planner, {username}!"}
        else:
            # return error message to populate alert
            return {"error": "Username and/or password are incorrect."}
    else:
        # return error message to populate alert
        return {"error": "Request was not submitted in JSON format."}


@app.route("/api/login", methods=["POST"])
def login():
    # default error message
    error = {"error": "Incorrect username and/or password."}
    if request.is_json:
        # clear previous login info
        session.clear()
        # extract data from request
        data = request.get_json()
        password = data["password"]
        username = data["username"]
        # check username and password validity
        if UserModel().check(username, password):
            # check to see if username is in database
            result = UserModel.query.filter_by(username=username).first()
            if not result:
                # return error message to populate alert
                return error
            else:
                # add login persistance to newly registered user
                user = UserModel.query.filter_by(username=username).first()
                if check_password_hash(user.password, password):
                    session["user_id"] = user.id
                    # return success message to populate alert
                    return {"success": f"Welcome back, {username}!"}
                else:
                    # return error message to populate alert
                    return error
        else:
            # return error message to populate alert
            return error
    else:
        # return error message
        return {"error": "Request was not submitted in JSON format."}


# persist certain session data in frontend without exposure of entire encrytped cookie
@app.route("/api/session")
def persist():
    # default session to be unauthorized
    _session_ = {"auth": False}
    # get session based on encrypted cookie
    userID = session.get("user_id")
    if userID:
        # set userID and auth on frontend if session valid
        _session_["auth"] = True
        _session_["userID"] = userID
    return _session_


@app.route("/api/logout")
@login_required
def logout():
    # Forget any user_id
    session.clear()
    # Redirect user to login form
    return {"success": "You have been logged out. We hope to see you soon!"}


@app.route("/api/constants")
def constants():
    # get page from query
    req = request.args.get("page")
    # return class CONSTANTS based on page
    if (req == "registration"):
        return UserModel().constants()
    elif (req == "templates"):
        return TemplateModel().constants()
    else:
        return {"error": "Your request was incorrectly formatted."}


@app.route("/api/templates", methods=["GET", "POST", "PATCH"])
@login_required
def templates():
    if request.method == "GET":
        # query TemplateModel for all templates
        templates = TemplateModel.query.all()
        # format results into JSON format
        results = [{
            "id": template.id,
            "owner_id": template.owner_id,
            "title": template.title,
            "description": template.description,
            "url": template.url,
            "amount": template.amount,
            "units": template.units,
        } for template in templates]
        # return count of results and result
        return {"count": len(results), "templates": results}
    if request.method == "POST":
        # grab user_id from encrypted session cookie
        owner_id = session["user_id"]
        # extract data from request
        data = request.get_json()
        title = data["title"]
        description = data["description"]
        url = data["url"]
        amount = data["amount"]
        units = data["units"]
        if TemplateModel().check(title, url, description, amount,
                                 units) and owner_id:
            # look for repeated title entries by same user
            result = TemplateModel.query.filter_by(owner_id=owner_id,
                                                   title=title).first()
            if result:
                # return error message
                return {
                    "error":
                    f"A template named \"{title}\" already exists. Please rename your template or edit the existing one."
                }
            else:
                # add template info to database
                template = TemplateModel(owner_id, title, url, description,
                                         amount, units)
                db.session.add(template)
                db.session.commit()
                return {
                    "success":
                    f"Your template, \"{title}\", has been successfully saved!"
                }
        else:
            # return error message
            return {
                "error":
                "Your template is incorrectly formatted. Please check your submission and try again."
            }


# run API server
if __name__ == '__main__':
    app.run()