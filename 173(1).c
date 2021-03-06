#pragma config(Sensor, port3,  gyro,           sensorVexIQ_Gyro)
#pragma config(Sensor, port9,  Color,          sensorVexIQ_ColorGrayscale)
#pragma config(Sensor, port11, touchled,       sensorVexIQ_LED)
#pragma config(Motor,  motor4,          hook,          tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor7,          left,          tmotorVexIQ, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motor8,          Omni,          tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor10,         Lift,          tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor12,         right,         tmotorVexIQ, PIDControl, reversed, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * Advanced Drive Control
 *
 * Example:
 *  adcMove(forward, 100, 100, gyroSensor);
 *  adcMove(leftward, 100, 50, gyroSensor, centerMotor);
 *  adcTurn(left, 45, gyroSensor);
 *  adcTurn(right, 90, gyroSensor);
 */
#include "Global_Angle_PID.c";
short i,armencoder;
void reset()
{
	setMotor(Lift,100);
	wait1Msec(1400);
	armencoder = getMotorEncoder(Lift)-30;
	setMotorTarget(Lift,-10,100);
}
task straight()
{
	while(1)
	{
		terror = 90-getGyroHeadingFloat(gyro);
		if (terror > 180){
			terror = terror - 360;
		}
		else if (terror < -180){
			terror = terror + 360;
		}

		terror=terror*ktp

		setMotorSpeed(left,-terror/2);
		setMotorSpeed(right,terror/2);
	}
}

task straight2()
{
	while(1)
	{
		terror = 270-getGyroHeadingFloat(gyro);
		if (terror > 180){
			terror = terror - 360;
		}
		else if (terror < -180){
			terror = terror + 360;
		}

		terror=terror*ktp

		setMotorSpeed(left,-terror/2);
		setMotorSpeed(right,terror/2);
	}
}

void raise(){
	setMotorTarget(Lift, armencoder, 100);
}
void lower(){
	setMotorTarget(Lift,-5,100);
}
void clamp(){
	setMotor(Hook,100);
	wait1Msec(350);
	stopMotor(Hook);
}


void open()
{
	setMotorTarget(Hook,-5,100)

}

void drop()
{
	moveMotor(Lift,140,degrees,-100);
	wait1Msec(200);
	open();
	waitUntilMotorStop(hook);
}
void leftside()
{
	constant_drive(220,70,0,1.5);
		Turn_to(90,0.7,0.7);
		constant_drive(450,70,90,1.5);
		clamp();
		raise();
		constant_drive(-160,-70,90,1.5);

		setmotor(Omni,100);
		wait1Msec(1600);
		stopMotor(Omni)

		constant_drive(230,90,90,1.5);
		strafe(-100,90,-100);
		drop();

		constant_drive(-200,-70,90,1.5);
		strafe(-1550,90,-100);
		constant_drive(240,90,90,1.5);
		constant_drive(-180,-80,90,1.5);

		setmotor(Omni,-100);
		starttask(straight);
		wait1Msec(3000);
		stopMotor(Omni)
		stoptask(straight);

		constant_drive(-380,-90,90,1.5);
		constant_drive(580,90,90,1.5);
		constant_drive(-200,-70,90,1.5);
		lower();
		strafe(470,90,100);
		constant_drive(200,70,90,1.5);
		clamp();
		raise();
		waitUntilMotorStop(Lift);
		Turn_to(53,0.7,0.7);
		constant_drive(70,70,53,1.5);
		drop();
		constant_drive(-200,-70,53,1.5);


}
task showscreen(){
	double l, r,o;
	while(true){
		l = getMotorEncoder(left);
		r = getMotorEncoder(right);
		o=getMotorEncoder(Omni);
		eraseUserScreenArea();
	  displayTextLine(1, "Heading: %d",  getgyroheading(gyro));
		displayTextLine(2, "terror: %d",  o);
	  displayTextLine(3, "l: %d", l);
		displayTextLine(4,"r: %d", r);
		wait1Msec(100);

	}
}



task main()
{
	///tune///

	///tune///
	setMotorBrakeMode(left,motorBrake);
	setMotorBrakeMode(right,motorBrake);
	setMotorBrakeMode(Omni,motorBrake);
	setTouchLEDColor(touchled,colorGreen);
	resetGyro(gyro);
	startTask(gyroTask);
	startTask(showscreen);
	playSound(soundTada);
	reset();
	/////

	/////

	while(1){
		waitUntil(getTouchLEDValue(port11)==1);
		//Drive(360,0);
		playSound(soundTada);

		//leftside();

		/*
		setMotorTarget(Hook,80,100);
		Turn_to(90);
		constant_drive(280,80,90,1.5);
		wait1Msec(500);
		open();
		strafe(-370,90,100)
		constant_drive(180,60,90,1.5);
		clamp();
		starttask(raise);
		waitUntilMotorStop(Lift);
		Turn_to(140);
		constant_drive(100,80,90,1.5);
		drop();
		*/
		//Turn_to(90,0.9,0.0);

		//

		waitUntil(getTouchLEDValue(port11)==1);

		constant_drive(220,70,0,1.5);
		Turn_to(270,0.7,0.7);
		constant_drive(450,70,270,1.5);
		clamp();
		raise();
		constant_drive(-190,-70,270,1.5);
		strafe(-600,270,-100)

		constant_drive(170,90,270,1.5);
		strafe(100,270,-100);
		drop();

		constant_drive(-190,-70,270,1.5);
		lower();
		strafe(900,270,100);
		constant_drive(260,70,270,1.5);
		clamp();
		raise();
		constant_drive(-160,-70,270,1.5);
		strafe(830,270,100);
		constant_drive(170,80,282,1.5);

		setMotor(Omni,100);
		starttask(straight2);
		waitUntil(SensorValue(Color)<140);
		stopMotor(Omni);
		stopTask(straight2);

		strafe(140,270,100);
		drop();
		constant_drive(-150,-60,270,1.5);
		lower();
		waitUntilMotorStop(Lift);
		constant_drive(190,50,270,1.5);
		clamp();
		raise();
		constant_drive(-100,-70,270,1.5);
		Turn_to(235,0.7,0.7);
		constant_drive(190,70,235,1.5);
		drop();

		constant_drive(-430,-70,225,1.5);
		lower();
		Turn_to(270,0.7,0.7);
		constant_drive(340,70,270,1.5);
		clamp();
		raise();

		constant_drive(-180,-70,270,1.5);
		waitUntilMotorStop(Lift);
		strafe(850,270,100);
		constant_drive(190,100,270,1.5);
		drop();
		constant_drive(-180,-80,270,1.5);
		lower();
		/*
		constant_drive(-170,-80,270,1.5);
		lower();
		wait1Msec(700);
		constant_drive(200,60,270,1.5);
		clamp();
		starttask(raise);
		constant_drive(-130,-60,270,1.5);
		Turn_to(230,0.7,0.7);
		constant_drive(220,70,230,1.5);
		drop();
		constant_drive(-450,-70,220,1.5);
		lower();
		Turn_to(270,0.7,0.7);
		constant_drive(350,80,270,1.5);
		clamp();
		starttask(raise);
		constant_drive(280,80,270,1.5);
		*/
		waitUntil(getTouchLEDValue(port11)==1);
		resetGyro(gyro);
		wait1Msec(500);
		leftside();


		setMotorBrakeMode(left,motorBrake);
		setMotorBrakeMode(right,motorBrake);
		setMotorSpeed(left,0);
		setMotorSpeed(right,0);
		setMotorBrakeMode(Omni,motorBrake);
		resetMotorEncoder(left);
		resetMotorEncoder(right);
		resetMotorEncoder(Omni);
		//



	}
}
