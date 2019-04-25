This sketch reads the distance value from an ultrasonic sensor and pushes the values to thingspeak channel.

The data is graphed in the thingspeak channel automatically so you get a nice visual representation of the data colected.




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Connections info is commented into the sketch (.ino  file), please refer !

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



-----> <B> Hardware required :</B>   NodeMCU dev Board 
			     Ultrasonic Sensor
	                     Arduino Uno (Optional)


------> <B> Note : </B> The sketch (.ino file) is inside the folder " thingspeakPushUltrasonic "  above. 






--- > <B> Thingspeak channel Setup : </B>



1.Create an account on thingspeak.com

2. After logging in click on 'New channel' button :

   
<img src="https://github.com/srihariash999/Arduino-Experiments/blob/master/Thingspeak%20%2B%20Ultrasonic%20Sensor/Screenshots/Screenshot%20from%202019-04-25%2013-32-50.png">


3. Then fill in the fields as required or as shown :

<img src="https://github.com/srihariash999/Arduino-Experiments/blob/master/Thingspeak%20%2B%20Ultrasonic%20Sensor/Screenshots/Screenshot%20from%202019-04-25%2013-33-50.png">


4. After saving, your channels page should be something like this:

<img src="https://github.com/srihariash999/Arduino-Experiments/blob/master/Thingspeak%20%2B%20Ultrasonic%20Sensor/Screenshots/Screenshot%20from%202019-04-25%2013-34-00.png">


5. Click on edit button to edit the detaiils of a field and Fill in as required :

<img src="https://github.com/srihariash999/Arduino-Experiments/blob/master/Thingspeak%20%2B%20Ultrasonic%20Sensor/Screenshots/Screenshot%20from%202019-04-25%2013-34-24.png">


6. Then copy your API key (WRITE) and paste it in the sketch where it is marked " ******** " :


<img src="https://github.com/srihariash999/Arduino-Experiments/blob/master/Thingspeak%20%2B%20Ultrasonic%20Sensor/Screenshots/Screenshot%20from%202019-04-25%2013-34-36.png">

7. ( Optional) If you want everyone to view your data, then make the channel public in 'sharing' options:


<img src="https://github.com/srihariash999/Arduino-Experiments/blob/master/Thingspeak%20%2B%20Ultrasonic%20Sensor/Screenshots/Screenshot%20from%202019-04-25%2013-42-58.png">















