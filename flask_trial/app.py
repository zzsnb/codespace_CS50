from flask import render_template, Flask, request

app = Flask(__name__)

@app.route("/")
def index():
    name = request.args.get("name","world")
    return render_template("index.html",name = name)
