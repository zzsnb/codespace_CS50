import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    # return apology("TODO")
    # select from assets
    rows = db.execute("SELECT * FROM assets WHERE id = ? ", user_id)
    # calculate total
    Total = 0
    if rows is not None:
        for row in rows:
            symbol = row["symbol"]
            shares = row["shares"]
            quote = lookup(symbol)
            price = quote["price"]
            row["price"] = price
            total = shares * price
            row["total"] = total
            Total += total

    # select from user to get cash
    cash = db.execute("SELECT cash FROM users WHERE id = ? ", user_id)
    cash = cash[0]["cash"]

    # calculate total
    Total += cash
    return render_template("portfolio.html", rows=rows, cash=cash, total=Total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # check the user's input
        if not request.form.get("symbol"):
            return apology("symbol must be entered")
        if not request.form.get("shares"):
            return apology("shares must be entered")
        if not request.form.get("shares").isdigit() or int(request.form.get("shares")) <= 0:
            return apology("INVALID SHARES")

        # get the form information
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        quote = lookup(symbol)

        # find the stock's price
        if quote is None:
            return apology("INVALID SYMBOL", 400)
        else:
            price = quote["price"]

        # caculate if the user can buy the number of stock
        user_id = int(session["user_id"])
        cash = db.execute("SELECT cash FROM users WHERE id = ? ", user_id)
        if cash[0]["cash"] < price * shares:
            return apology("can't afford", 400)
        else:
            # return apology("TODO")
            # change the number of cash I have in the users table
            db.execute("UPDATE users SET cash = ? WHERE id = ? ",
                       cash[0]["cash"] - price * shares, user_id)

            # change the number of assets I have int the assets table
            result = db.execute(
                "SELECT * FROM assets WHERE id = ? AND symbol = ? ", user_id, symbol)
            if not result:
                db.execute("INSERT INTO assets (id, symbol, shares) VALUES (?, ?, ?)",
                           user_id, symbol, shares)
            else:
                primary = result[0]["shares"]
                db.execute("UPDATE assets SET shares = ? WHERE id = ? AND symbol = ?",
                           primary + shares, user_id, symbol)

            # append new event in the new history table(put aside the time(default))
            db.execute("INSERT INTO history (id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                       user_id, symbol, shares, price)

            # return to /
            return redirect("/")

    else:
        # render the page when the user first enter
        return render_template("buy.html")
    # return apology("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # return apology("TODO")
    rows = db.execute("SELECT * FROM history WHERE id = ? ", session["user_id"])
    return render_template("history.html", rows=rows)


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
        # 这里是已经登陆成功了，所以重新redirect到首页

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
            return apology("please enter Symbol", 400)
        else:
            symbol = request.form.get("symbol")
            quote = lookup(symbol)
            if quote is None:
                return apology("INVALID SYMBOL", 400)
            else:
                name = quote["name"]
                price = quote["price"]
                Symbol = quote["symbol"]
                return render_template("quoted.html", name=name, price=price, symbol=Symbol)
    else:
        return render_template("quote.html")
    # return apology("TODO")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        elif not request.form.get("confirmation"):
            return apology("please enter the password again", 400)
        elif not request.form.get("confirmation") == request.form.get("password"):
            return apology("two times' password are different", 400)
        else:
            username = request.form.get("username")
            password = request.form.get("password")
            try:
                Password = generate_password_hash(password, method='pbkdf2', salt_length=16)
                db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, Password)
            except ValueError:
                return apology("username has existed", 400)
        return redirect("/login")
    else:
        return render_template("register.html")
        # render the page when the user first access

    # return apology("TODO")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # return apology("TODO")
    user_id = session["user_id"]
    result = db.execute("SELECT symbol FROM assets WHERE id = ? ", user_id)
    symbols = [row["symbol"] for row in result]
    print(symbols)
    if request.method == "POST":
        # return apology("TODO")

        # check the users input

        if not request.form.get("symbol"):
            return apology("symbol must be chose")
        if not request.form.get("shares"):
            return apology("shares must be entered")
        if not request.form.get("shares").isdigit() or int(request.form.get("shares")) <= 0:
            return apology("INVALID SHARES")

        # get the form information
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        # check if there are this symbol in the assets (to prevent bad input)
        if symbol not in symbols:
            return apology("INVALID symbol")

        # check if there are such many shares for this symbol
        primary = db.execute(
            "SELECT shares FROM assets WHERE id = ? AND symbol = ? ", user_id, symbol)
        primary = int(primary[0]["shares"])
        if shares > primary:
            return apology("INVALID shares")

        # look up the price of the stock
        quote = lookup(symbol)
        if quote is not None:
            price = quote["price"]
        else:
            return apology("INVALID SYMBOL", 402)

        # change the users table for cash, assets table for symbol, and the history table
        cash = db.execute("SELECT cash FROM users WHERE id = ? ", user_id)
        db.execute("UPDATE users SET cash = ? WHERE id = ? ",
                   cash[0]["cash"] + price * shares, user_id)
        if primary == shares:  # delete the row for assets if there is no any this company's stock
            db.execute("DELETE FROM assets WHERE id = ? AND symbol = ? ", user_id, symbol)
        else:
            db.execute("UPDATE assets SET shares = ? WHERE id = ? AND symbol = ? ",
                       primary - shares, user_id, symbol)
        db.execute("INSERT INTO history (id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                   user_id, symbol, -shares, price)

        # return to / with message "Sold"
        return redirect("/")
    else:
        return render_template("sell.html", symbols=symbols)
