#imports
from flask import Flask, request, jsonify
from threading import Thread
import cv2
import base64
import numpy as np

app = Flask('')

@app.route("/", methods=["POST", "GET"])
def home():
    if request.method == "POST":                             # checks if there was a post
        img_str = request.form["img"]                        # the string image posted by the phone

        bs4img = base64.b64decode(img_str)                   # decode's string img

        img_as_np = np.frombuffer(bs4img, dtype=np.uint8) 

        # img = cv2.imdecode(img_as_np, flags=1)               

        # cv2.imshow("img", img)
        

        #del(img)

        return jsonify({"name" : "aditya"})           

    #basic html code for page if something is not posted

    return '<h1>WebServer for AI Car</h1> <br> <p>This is a WebServer for using AI for an automated car. <br> Check out our <a href="https://www.youtube.com/watch?v=dQw4w9WgXcQ&ab_channel=RickAstley">GitHub page</a> to learn more.'


def run():
    app.run(host='0.0.0.0', debug=True, port=1234)


def keep_alive():
    t = Thread(target=run)
    t.start()


if __name__ == "__main__":
    keep_alive()         #running the flask app