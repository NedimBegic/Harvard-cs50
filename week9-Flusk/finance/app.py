import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.globals.update(usd=usd)

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

    # Get user's cash balance
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    # Get user's stocks and their quantities
    stocks = db.execute("""
        SELECT symbol, SUM(shares) as total_shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        HAVING total_shares > 0
    """, session["user_id"])

    # Calculate total value of each stock and overall portfolio
    portfolio = []
    total_portfolio_value = user_cash

    for stock in stocks:
        stock_info = lookup(stock["symbol"])
        total_value = stock_info["price"] * stock["total_shares"]
        total_portfolio_value += total_value
        portfolio.append({
            "symbol": stock["symbol"],
            "name": stock_info["name"],
            "shares": stock["total_shares"],
            "price": stock_info["price"],
            "total_value": total_value
        })

    return render_template("index.html", user_cash=user_cash, portfolio=portfolio, total_portfolio_value=total_portfolio_value)



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock symbol")

        # Ensure shares were submitted and are positive integers
        try:
            shares = int(request.form.get("shares"))
            if shares <= 0:
                raise ValueError
        except (ValueError, TypeError):
            return apology("must provide a positive integer for shares")

        # Lookup the stock symbol
        stock_info = lookup(request.form.get("symbol"))

        # Check if the symbol is valid
        if not stock_info:
            return apology("invalid stock symbol")

        # Get the user's cash balance
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        # Calculate the total cost of the shares
        total_cost = stock_info["price"] * shares

        # Check if the user can afford the shares
        if total_cost > user_cash:
            return apology("insufficient funds")

        # Update the user's cash balance
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, session["user_id"])

        # Record the purchase in the database
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, transacted_at) VALUES (?, ?, ?, ?, CURRENT_TIMESTAMP)",
                   session["user_id"], stock_info["symbol"], shares, stock_info["price"])

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")



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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock symbol")

        # Lookup the stock symbol
        stock_info = lookup(request.form.get("symbol"))

        # Check if the symbol is valid
        if not stock_info:
            return apology("invalid stock symbol")

        # Render the quoted template
        return render_template("quoted.html", stock=stock_info)

    # User reached route via GET (as by clicking a link or via redirect)
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

        # Ensure password confirmation matches
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords must match", 400)

        # Query database for existing username
        existing_user = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if existing_user:
            return apology("username already exists", 400)

        # Insert new user into database
        user_id = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                             request.form.get("username"), generate_password_hash(request.form.get("password")))

        # Remember which user has logged in
        session["user_id"] = user_id

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        # Ensure symbol was submitted
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must select a stock to sell")

        # Ensure shares were submitted and are positive integers
        try:
            shares = int(request.form.get("shares"))
            if shares <= 0:
                raise ValueError
        except (ValueError, TypeError):
            return apology("must provide a positive integer for shares")

        # Check if the user owns enough shares to sell
        user_shares = db.execute("""
            SELECT SUM(shares) as total_shares
            FROM transactions
            WHERE user_id = ? AND symbol = ?
            GROUP BY symbol
        """, session["user_id"], symbol)

        if not user_shares or user_shares[0]["total_shares"] < shares:
            return apology("not enough shares to sell")

        # Lookup the stock symbol
        stock_info = lookup(symbol)

        # Calculate the total value of the sold shares
        total_value = stock_info["price"] * shares

        # Update the user's cash balance
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", total_value, session["user_id"])

        # Record the sale in the database
        db.execute("""
            INSERT INTO transactions (user_id, symbol, shares, price, transacted_at)
            VALUES (?, ?, ?, ?, CURRENT_TIMESTAMP)
        """, session["user_id"], symbol, -shares, stock_info["price"])

        # Redirect user to home page
        return redirect("/")

    else:
        # Get the symbols of stocks owned by the user
        stocks = db.execute("""
            SELECT symbol
            FROM transactions
            WHERE user_id = ?
            GROUP BY symbol
            HAVING SUM(shares) > 0
        """, session["user_id"])

        return render_template("sell.html", stocks=stocks)

