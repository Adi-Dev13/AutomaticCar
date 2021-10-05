This is all the code used for making the Self Driving car for the WRO competetion.

The car is controlled by a Arduino nano micro controller. It takes input from the sonar sensor and detects if there is an object in front of it or not. If there is an object in front of the car
then the car stops. Then the servo motor rotates, rotating the sonar sensor. While it rotates the arduino checks which directions whould be the best for it to go. Once it detects a certain direction
the car then rotates towards that direction and avoids obstacles in this way.

The motors driver we choose to go with is the L298N H-bridge motor driver. We choose to go with this as it was the easiest to work with and works very well. The arduino controlls the motor by
making the motors move left or right depending on the direction it needs to go to. To turn left the left motors would turn backwards and right motors front. So the car would rotate towards the left
on the spot. This is similar to how tanks rotate.

The only library used for this project is Servo Library which allows us to controll servo motors easily. Apart from that all the code in this project was written by us.