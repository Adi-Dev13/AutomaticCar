# imports
from flask import Flask, request
import cv2
import base64
import numpy as np


app = Flask(__name__)

a= []

# To remove the background of the frame
remove_background = cv2.createBackgroundSubtractorMOG2(history=25, varThreshold=25, detectShadows=True)
main_masking = np.ones((10, 10), np.uint8)

# Inputs frames as post request from phone and detects the objects
@app.route("/", methods=["POST", "GET"])
def home():

    if request.method == "POST":

        # Inputing and decoding string image
        img_str = request.form["img"]
        img_decoded = base64.b64decode(img_str)  

        img_as_np = np.frombuffer(img_decoded, dtype=np.uint8)
        img = cv2.imdecode(img_as_np, flags=1)

        result = Detect(img)

        del(img_str)
        del(img_decoded)
        del(img_as_np)
        del(img)

        print(f'{result = }')

        return result

    return '<h1>WebServer for AI Car</h1> <br> <p>This is a WebServer for using AI for an automated car. <br> Check out our <a href="https://www.youtube.com/watch?v=dQw4w9WgXcQ&ab_channel=RickAstley">GitHub page</a> to learn more.'

# Function to detect objects in the frame
def Detect(frame):

    foreground_mask = remove_background.apply(frame)
    foreground_mask = cv2.morphologyEx(foreground_mask, cv2.MORPH_CLOSE, main_masking)
    foreground_mask = cv2.medianBlur(foreground_mask, 7)
    none, foreground_mask = cv2.threshold(foreground_mask, 254, 255, cv2.THRESH_BINARY)

    foreground_mask_contour = foreground_mask
    contours, hierarchy = cv2.findContours(foreground_mask_contour, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)[-2:]

    detected_object_area = [cv2.contourArea(c) for c in contours]

    del(foreground_mask)
    del(foreground_mask_contour)

    print(f"{ detected_object_area =  }")

    if len(detected_object_area) < 1:
        return "Object Not Detected"
    else:
        return "Object Detected"



def run():
  app.run(host='0.0.0.0',port=8080)

if __name__ == "__main__":
    run()