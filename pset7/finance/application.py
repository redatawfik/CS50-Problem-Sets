import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    userId = session["user_id"]

    purchaesRows = db.execute("SELECT symbol, shares FROM purchase WHERE userId = :uid", uid=userId)

    cash = db.execute("SELECT cash FROM users WHERE id = :uid", uid=userId)
    cash = cash[0]["cash"]

    countDic = {}
    for row in purchaesRows:
        if row['symbol'] in countDic:
            countDic[row['symbol']] += row['shares']
        else:
            countDic[row['symbol']] = row['shares']

    data = []
    final_cash = cash

    for key in countDic:
        quote = lookup(key)
        if countDic[key] != 0:
            total = (quote['price'] * countDic[key])
            final_cash += total
            dic = {'symbil': key, 'name': quote['name'], 'price': usd(quote['price']), 'shares': countDic[key], 'total': usd(total)}
            data.append(dic)

    return render_template("index.html", data=data, cash=usd(cash), final=usd(final_cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("Missing symbol", 400)

        if not shares:
            return apology("Missing shares", 400)

        if shares.isdigit() == False:
            return apology("Invalid share number", 400)

        quote = lookup(request.form.get("symbol"))

        if not quote:
            return apology("Invalid symbol")

        userId = session["user_id"]

        shares = int(shares)

        cash = db.execute("SELECT cash FROM users WHERE id = :uid", uid=userId)
        cash = cash[0]["cash"]
        cost = shares * quote["price"]

        if cost > cash:
            return apology("Can't afford", 400)

        time = datetime.now()

        db.execute("INSERT INTO purchase (userId, symbol, price, shares, time) VALUES (:userId, :symbol, :price, :shares, :time)",
                   userId=userId, symbol=quote["symbol"], price=quote["price"], shares=shares, time=time)

        newCash = cash - cost
        db.execute("UPDATE users SET cash = :cash WHERE id = :uid", cash=newCash, uid=userId)
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    userId = session["user_id"]

    data = db.execute("SELECT symbol, shares, price, time FROM purchase WHERE userId = :uid", uid=userId)

    for row in data:
        row["price"] = usd(row["price"])

    return render_template("history.html", data=data)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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

        if not request.form.get("symbol"):
            return apology("Missing symbol", 400)

        quote = lookup(request.form.get("symbol"))

        if not quote:
            return apology("Invalid symbol", 400)

        quote["price"] = usd(quote["price"])

        return render_template("quoted.html", company=quote['name'], symbol=quote['symbol'], price=quote['price'])
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must confirm password", 400)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password don't match", 400)

        hashed = generate_password_hash(request.form.get("password"), method='plain')
        rowId = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
                           username=request.form.get("username"), hash=hashed)

        if not rowId:
            return apology("username already exist", 400)

        session["user_id"] = rowId

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    userId = session["user_id"]

    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("Missing symbol", 400)

        if not shares:
            return apology("Missing shares", 400)

        if shares.isdigit() == False:
            return apology("Invalid share number", 400)

        shares = int(shares)
        my_shares = db.execute(
            "SELECT SUM(shares) AS total FROM purchase WHERE userId = :uid AND symbol = :symbol", uid=userId, symbol=symbol)

        if my_shares[0]["total"] < shares:
            return apology("too many shares", 400)

        quote = lookup(symbol)
        time = datetime.now()

        db.execute("INSERT INTO purchase (userId, symbol, price, shares, time) VALUES (:userId, :symbol, :price, :shares, :time)",
                   userId=userId, symbol=quote["symbol"], price=quote["price"], shares=shares * -1, time=time)

        money = quote["price"] * shares
        cash = db.execute("SELECT cash FROM users WHERE id = :uid", uid=userId)
        cash = cash[0]["cash"] + money
        db.execute("UPDATE users SET cash = :cash WHERE id = :uid", cash=cash, uid=userId)

        return redirect("/")

    else:
        dist = db.execute("SELECT DISTINCT symbol FROM purchase WHERE userId = :uid", uid=userId)
        return render_template("sell.html", data=dist)


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    """Chnge password"""

    userId = session["user_id"]

    if request.method == "POST":
        row = db.execute("SELECT hash FROM users WHERE id = :uid", uid=userId)

        # Ensure Old password was submmited
        if not request.form.get("old-password"):
            return apology("Missing password", 400)

        # Ensure new password was submmited
        if not request.form.get("password"):
            return apology("Missing password", 400)

        # Ensure password confirmation was submmited
        if not request.form.get("confirmation"):
            return apology("Missing password confirmation", 400)

        # check if password is correct
        if not check_password_hash(row[0]["hash"], request.form.get("old-password")):
            return apology("invalid password", 403)

        if request.form.get("password") != request.form.get("confirmation"):
            return apology("password don't match", 400)

        # Update user password in database
        db.execute("UPDATE users SET hash = :password WHERE id = :uid",
                   password=generate_password_hash(request.form.get("password"), method='plain'), uid=userId)

        return redirect("/")

    else:
        return render_template("change_password.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
