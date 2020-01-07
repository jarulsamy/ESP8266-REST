#!/usr/bin/python3

from flask import request, jsonify, abort, make_response
from flask_api import FlaskAPI

from colorama import init
from termcolor import colored

from datetime import datetime

app = FlaskAPI(__name__)

temps = {
    "celsius": {"value": 00, "last_modified": ""},
    "fahrenheit": {"value": 00, "last_modified": ""}
}

# Dummy root page
@app.route("/")
def index():
    return "Hello, World!"


# GET all temps
@app.route("/api/v1.0/temps", methods=["GET"])
def get_temps():
    return jsonify({"temps": temps})


# GET specific temp
@app.route("/api/v1.0/temps/<string:_type>", methods=["GET"])
def get_temp(_type):
    if _type not in temps:
        abort(404)
    return jsonify({"temps": temps[_type]})


# Create POST endpoints based on type.
@app.route("/api/v1.0/temps/<string:_type>", methods=["POST"])
def set_specific_temp(_type):
    if not request.json or _type not in temps:
        abort(400)

    temps[_type]["value"] = request.json["value"]
    return jsonify({"temps": temps}), 201

# POST to set BOTH temperatures simultaneously.
@app.route("/api/v1.0/temps", methods=["POST"])
def set_temps():
    if not request.json or temps.keys() != request.json.keys():
        abort(400)

    now = datetime.now()
    for i in temps.keys():
        temps[i]["value"] = request.json[i]["value"]
        temps[i]["last_modified"] = now.strftime("%d/%m/%Y %H:%M:%S")
    print(colored(temps, "grey", "on_yellow"))
    return jsonify({"temps": temps}), 201

# Error handling
@app.errorhandler(404)
def not_found(error):
    return make_response(jsonify({"error": "Not found"}), 404)


if __name__ == "__main__":
    app.run(host="0.0.0.0", debug=True)
