from flask import render_template, Flask, request

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")
@app.route("/route")
def index():
    return render_template("route.html",)
