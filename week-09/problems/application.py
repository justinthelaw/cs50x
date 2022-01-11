import os
import uuid

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index(success=None):
    """Show portfolio of stocks"""

    userID = session["user_id"]
    user = db.execute("SELECT * FROM users WHERE id = ?", userID)[0]
    portfolio = db.execute("SELECT * FROM stocks WHERE userID = ?", userID)
    if len(portfolio) < 1:
        portfolio = [
            # {
            #     "symbol": "NFLX",
            #     "companyName": "Netflix, Inc.",
            #     "latestPrice": 318.83,
            #     "shares": 1,
            # }
        ]
    total = user["cash"]
    for ticker in portfolio:
        latestPrice = lookup(ticker["symbol"])["price"]
        ticker["latestPrice"] = latestPrice
        ticker["total"] = round(ticker["shares"] * latestPrice, 2)
        total += ticker["total"]
    return render_template(
        "home.html",
        user=user["username"],
        portfolio=portfolio,
        cash=user["cash"],
        total=total,
        success=success,
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if symbol and shares:
            # necessary data to lookup quote, buy stock, and modify the users and stocks tables
            stock = lookup(symbol)
            symbol = stock["symbol"]
            companyName = stock["name"]
            latestPrice = stock["price"]
            userID = session["user_id"]
            cost = round(latestPrice, 2) * float(shares)
            currentCash = db.execute("SELECT cash FROM users WHERE id = ?", userID)[0][
                "cash"
            ]
            alreadyOwns = db.execute(
                "SELECT * FROM stocks WHERE userID = ? AND symbol = ?", userID, symbol
            )
            if currentCash >= cost:
                if len(alreadyOwns) == 0:
                    # execute insertion of stock into stocks table based on userID and user input
                    db.execute(
                        "INSERT INTO stocks (symbol, companyName, shares, userID) VALUES(?, ?, ?, ?)",
                        symbol,
                        companyName,
                        shares,
                        userID,
                    )
                else:
                    db.execute(
                        "UPDATE stocks SET shares = ? WHERE userID = ? AND symbol = ?",
                        alreadyOwns[0]["shares"] + int(shares),
                        userID,
                        symbol,
                    )
                # update user cash amount
                db.execute(
                    "UPDATE users SET cash = ? WHERE id = ?",
                    currentCash - cost,
                    userID,
                )
                # insert transaction into history
                db.execute(
                    "INSERT INTO history (action, symbol, companyName, latestPrice, userID, shares) VALUES(?, ?, ?, ?, ?, ?)",
                    "BUY",
                    symbol,
                    companyName,
                    latestPrice,
                    userID,
                    shares,
                )
                return index(f"Success! Bought {shares} shares of {symbol}.")
            else:
                return render_template(
                    "buy.html",
                    error=f"Lacking {usd(cost - currentCash)} to buy {shares} shares of {symbol}.",
                )
        else:
            return render_template(
                "buy.html", error=f"Please provide a symbol and number of shares."
            )
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    userID = session["user_id"]
    user = db.execute("SELECT * FROM users WHERE id = ?", userID)[0]
    history = db.execute("SELECT * FROM history WHERE userID = ?", userID)
    for ticker in history:
        latestPrice = lookup(ticker["symbol"])["price"]
        ticker["latestPrice"] = latestPrice
        ticker["total"] = round(ticker["shares"] * latestPrice, 2)
    return render_template(
        "history.html",
        user=user["username"],
        history=history,
    )


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        result = lookup(symbol)
        if not symbol:
            return render_template("quote.html", error="Please input a symbol.")
        elif result:
            return render_template("quoted.html", result=result)
        else:
            return render_template(
                "quote.html",
                error="Search failed, please try looking up a different symbol.",
            )

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        username = request.form.get("username")
        unhashedPassword = request.form.get("password")
        confirmPassword = request.form.get("confirm")
        # for verifying username is unique
        exists = db.execute("SELECT username FROM users")
        userDict = {"username": username}
        # Ensure username was submitted
        if not username:
            return apology("must provide username", 403)
        # gracefully catch existing username
        elif userDict in exists:
            return apology("username taken", 403)
        # Ensure password was submitted
        elif not unhashedPassword:
            return apology("must provide password", 403)
        # Ensure password is repeated
        elif confirmPassword != unhashedPassword:
            return apology("passwords do not match", 403)

        hashedPassword = generate_password_hash(unhashedPassword)
        # Insert password and username into db
        db.execute(
            "INSERT INTO users (username, hash) VALUES(?, ?)",
            username,
            hashedPassword,
        )
        # Redirect user to login with success message
        return render_template(
            "login.html", success="Registered successfully! Please login to continue."
        )

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if symbol and shares:
            # necessary data to lookup quote, buy stock, and modify the users and stocks tables
            stock = lookup(symbol)
            symbol = stock["symbol"]
            latestPrice = stock["price"]
            companyName = stock["name"]
            userID = session["user_id"]
            cost = round(latestPrice, 2) * float(shares)
            currentCash = db.execute("SELECT cash FROM users WHERE id = ?", userID)[0][
                "cash"
            ]
            alreadyOwns = db.execute(
                "SELECT * FROM stocks WHERE userID = ? AND symbol = ?", userID, symbol
            )
            if alreadyOwns:
                db.execute(
                    "UPDATE stocks SET shares = ? WHERE userID = ? AND symbol = ?",
                    alreadyOwns[0]["shares"] - int(shares),
                    userID,
                    symbol,
                )
                db.execute("DELETE FROM stocks WHERE shares = 0")
                # update user cash amount
                db.execute(
                    "UPDATE users SET cash = ? WHERE id = ?",
                    currentCash + cost,
                    userID,
                )
                # insert transaction into history
                db.execute(
                    "INSERT INTO history (action, symbol, companyName, latestPrice, userID, shares) VALUES(?, ?, ?, ?, ?, ?)",
                    "SELL",
                    symbol,
                    companyName,
                    latestPrice,
                    userID,
                    shares,
                )
                return index(f"Success! Sold {shares} shares of {symbol}.")
            else:
                return render_template(
                    "sell.html",
                    error=f"You do not own {shares} of {symbol}. Please try again.",
                )
        else:
            return render_template(
                "sell.html", error=f"Please provide a symbol and number of shares."
            )
    else:
        symbols = []
        userID = session["user_id"]
        portfolio = db.execute("SELECT * FROM stocks WHERE userID = ?", userID)
        for ticker in portfolio:
            symbols.append(ticker["symbol"])
        return render_template("sell.html", symbols=symbols)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
