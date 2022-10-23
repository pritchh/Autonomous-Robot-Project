#pragma config(Sensor, in1,    InfraCollector, sensorReflection)
#pragma config(Sensor, I2C_1,  leftMotor,         sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, dgtl4,  button1,        sensorTouch)
#pragma config(Sensor, dgtl5,  button4,        sensorTouch)
#pragma config(Sensor, dgtl7,  button3,        sensorTouch)
#pragma config(Sensor, dgtl8,  sonarSensor,    sensorSONAR_cm)
#pragma config(Sensor, dgtl12, button2,        sensorTouch)
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port9,           pingmotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
																				/*leftMotor is our left wheel motor, rightMotor is our right wheel motor, pingmotor is our placement
																				motor, sonarSensor is our ultrasonic sensor, and infraCollector is our IR phototransistor. */



int found = 0;                          //int for the pls find ir search function return value
void wall_avoidance(){  								/*this function is referenced when we want our robot to check if either of our front bumpers
																				    have been pressed, and then it will reverse, turn, and drive forward*/

if(SensorValue[button3] == 1){

motor[leftMotor] = -60;
motor[rightMotor] = 30;
wait1Msec(1300);

motor[rightMotor] = 40;
motor[leftMotor] = 40;

}


if(SensorValue[button4] == 1){

motor[leftMotor] = 30;
motor[rightMotor] = -60;
wait1Msec(1300);

motor[rightMotor] = 40;
motor[leftMotor] = 40;

}
}




void anti_wall(){      									/*Anti wall is our function that starts off our code. We start by finding the largest open \
																					space and driving towards it in hopes that it will give our find ir function a higher
																					chance of actually being able to see the light emitter*/

while(SensorValue(sonarSensor) < 150){     //While less than max distance, turn, once it faces max distance, drive towards it

motor[rightMotor] = -60;
motor[leftMotor] = 60;
wall_avoidance();
wait1Msec(1250);


}

motor[rightMotor] = -60;
motor[leftMotor] = -60;
wait1Msec(3000);



wall_avoidance();


motor[rightMotor] = 0;
motor[leftMotor] = 0;


}


int pls_find_IR(){                            /* This is our function used to find the ir light emitter. The function returns an int as in
																							main we use a while loop to increment this. If the code returns 1, we know that our ROBOT
																							didn't find the ir light emitter. In which case, we drive forward for a couple of seconds
																								using the function drive forward,
																							and then re go through pls find ir. By doing this, we will keep trying to find the ir
																							until we do, and if we dont, we will keep driving forwads until eventually, we may hit a
																							bumper which would change the direction of our robot. In any case, after a few itterations
																							of returning one and driving forward, the robot will find the ir light in our testing.*/


while(SensorValue(InfraCollector) > 130){
motor[rightMotor] = 90;
motor[leftMotor] = -90;
wall_avoidance();

if(getMotorEncoder(leftMotor) > (4581)){         /*So if the robot does a full circle without finding the ir, the function returns 1
																									and breaks*/
return 1;
break;
}
}

if(SensorValue(InfraCollector) <=123){ 					//If the robot senses the ir, it will now drive towards it until its within 50cm

 motor[rightMotor] = 0;
motor[leftMotor] = 0;

}
while(SensorValue[sonarSensor] > 50){
motor[rightMotor] = -30;
motor[leftMotor] = -30;
wall_avoidance();


}
motor[rightMotor] = 0;
motor[leftMotor] = 0;
return 0;
}




void placement(){																	//Places the ball. Pretty straight forward. Drives towards it slowly and then places.





while(SensorValue[sonarSensor] > 14){

motor[rightMotor] = -30;
motor[leftMotor] = -30;
wall_avoidance();
}



motor[rightMotor] = 0;
motor[leftMotor] = 0;


wall_avoidance();
wait1Msec(2000);
motor[pingmotor] = -35;
wait1Msec(1000);
motor[pingmotor] = 27;
wait1Msec(750);
motor[pingmotor] = 0;


}






void drive_forward(){																	/*This function is used in combination with find ir to break out of
																											an infinite loop where we arent sensing the ir light (the while found == 1).*/

motor[rightMotor] = -60;
motor[leftMotor] = -60;
wait1Msec (1000);
}




void back_away(){																				/* Reverses and then turns, and then drives to the wall and does
																												a little dance :)*/
while(SensorValue(sonarSensor) < 30){
motor[leftMotor] = 60;
motor[rightMotor] = 60;
wait1Msec(3000);

motor[leftMotor] = -60;
motor[rightMotor] = 60;
wait1Msec(2500);
}
while(SensorValue(sonarSensor) > 12){
motor[rightMotor] = -60;
motor[leftMotor] = -60;

}
motor[rightMotor] = 0;
motor[leftMotor] = 0;

for(int i = 0; i < 10; i++){
motor[pingmotor] = -55;
wait1Msec(200);
motor[pingmotor] = 50;
wait1Msec(200);
motor[pingmotor] = 0;
}
}




task main()
{

while(true){                                       /*This code is waiting in an infinite loop for us to press the button. Then, we run
																										anti wall to try and find open space. Then we do the While found == 1 loop until
																										the ir is detected within our range.
																										 Then, once ir is found, it breaks out of the while loop, does placement,
																										and backs up!!!!!!!!! Cheers!*/
if(SensorValue(button1) == 1){

anti_wall();

found = pls_find_IR();

while(found == 1){

drive_forward();

found = pls_find_IR();

}










placement();

back_away();
break;



}

}
}
