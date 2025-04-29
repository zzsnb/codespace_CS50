import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        if not name: #检查是否为空
            return redirect("/")
        month = request.form.get("month")
        if not month or int(month) < 1 or int(month) > 12: #检查是否为空
            return redirect("/")
        try:
            month=int(month)
        except ValueError:
            return redirect("/")
        day = request.form.get("day")
        if not day:
            return redirect("/")

        db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays = birthdays)

@app.route('/delete', methods=['POST'])
def delete_row():
    data = request.get_json()  # 接收JSON数据
    row_id = data.get('row_id')  # 获取row_id
    if row_id:
        try:
            db.execute("DELETE FROM birthdays WHERE id = ?", (row_id,))
            return jsonify({'status': 'success'})  # 返回成功状态
        except Exception as e:
            return jsonify({'status': 'error', 'message': str(e)}), 400
    return jsonify({'status': 'error', 'message': 'Invalid row ID'}), 400
