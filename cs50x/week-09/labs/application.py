import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

BIRTHDAYS = [{"name": "Justin", "month": 1, "day": 16}]
ERROR = ""


@app.route("/", methods=["GET", "POST"])
def index():

    global ERROR

    if request.method == "POST":
        ERROR = ""
        name = request.form.get("name")
        if not name:
            ERROR = "Missing Name"
        month = request.form.get("month")
        if not month:
            if len(ERROR) > 0:
                ERROR += ", "
            ERROR += "Missing Month"
        day = request.form.get("day")
        if not day:
            if len(ERROR) > 0:
                ERROR += ", "
            ERROR += "Missing Day"
        if name and day and month:
            ERROR = ""
            db.execute(
                "INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)",
                name,
                month,
                day,
            )

        return redirect("/")
    else:
        BIRTHDAYS = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=BIRTHDAYS, error=ERROR)
