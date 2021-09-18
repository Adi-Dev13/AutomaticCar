This is all the code used for making the Self Driving car for the WRO competetion.

The car is controlled by a NodeMCU micro controller. A phone with an app made by us is attached and its camera frames are sent to a web server made using flask and python. The webserver detects the objects in the image using openCV and numpy and then detects where the car needs to go to avoid it. 
It then send the instructions to the nodeMCU which controlls the motor using an l298N motor driver.