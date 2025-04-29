from flask import render_template, Flask, request

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")
@app.route("/greet")
def greet():
    return render_template("greet.html",name=request.args.get("name", "world"))
