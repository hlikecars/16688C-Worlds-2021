#pragma config(Sensor, port3,  gyro,           sensorVexIQ_Gyro)
#pragma config(Sensor, port11, toucharm,       sensorVexIQ_LED)
#pragma config(Motor,  motor4,          Hook,          tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor5,          stick,         tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor7,          leftMotor,     tmotorVexIQ, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motor8,          omni,          tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor10,         Lift,          tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor12,         rightMotor,    tmotorVexIQ, PIDControl, reversed, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int threshold = 10;
int leftSpeed = 0;
int rightSpeed = 0;
int LiftH;
int gyrovalue;
int waiting;
int up;
int status;
float armencoder;
bool swing=False;
int OmniSpeed;
bool disablestick;

task raise(){
	setMotorTarget(Lift, armencoder-10, 100);
}
void lower(){
	setMotorTarget(Lift,-15,100);
}
task clamp(){
	setMotor(Hook,-100);
	wait1Msec(350);
	stopMotor(Hook);
}
task anti_ghosting(){
	while(true){
		if(getJoystickValue(ChA) > threshold || getJoystickValue(ChA) < -threshold || getJoystickValue(ChB) > threshold || getJoystickValue(ChB) < -threshold||abs(getJoystickValue(ChC))>10)
		{

			leftSpeed = getJoystickValue(ChA) + (getJoystickValue(ChB))/1.15;	// (y + x)
			rightSpeed = getJoystickValue(ChA) - (getJoystickValue(ChB))/1.15;
			OmniSpeed = getJoystickValue(ChC);

			setMotorSpeed(leftMotor, leftSpeed);
			setMotorSpeed(rightMotor, rightSpeed);
			setMotorSpeed(Omni, OmniSpeed);
		}
		else
		{
			setMotorSpeed(leftMotor, 0);
			setMotorSpeed(rightMotor, 0);
			setMotorSpeed(Omni,0);
		}

	}
}

task main()
{


	setTouchLEDColor(toucharm,colorOrange);
	waitUntil(getTouchLEDValue(toucharm)==True);
	resetMotorEncoder(stick);
	resetMotorEncoder(Lift);
	resetMotorEncoder(Hook);


	//intialize
	setMotor(Lift,100);
	wait1Msec(1400);
	armencoder = getMotorEncoder(Lift);
	setMotorTarget(Lift,-10,100);
	setMotorBrakeMode(Omni,motorBrake);
	///

	startTask(anti_ghosting);
	disablestick=True;
	//startTask(swerve);


	//initializing
	setTouchLEDColor(toucharm,colorYellow);


	setMotorBrakeMode(leftMotor,motorBrake);
	setMotorBrakeMode(rightMotor,motorBrake);

	while(true)
	{

		//If the "L-Up" isn't pressed, but "L-Down" is, we'll set the motor to run forward.
		if(getJoystickValue(BtnRDown) == 1)
		{

			startTask(clamp);
			//wait1Msec(750);
			//stopTask(clamp);
			//setMotorSpeed(Hook,-100);
		}
		else if(getJoystickValue(BtnRUp) == 1)
		{
			setMotorTarget(Hook,95,100);
		}


		if(getJoystickValue(BtnEUp) == 1)
		{
			setMotorTarget(stick,0,100);
			setMotorTarget(Lift,60,100);
			setMotorTarget(stick,0,100);
			waitUntilMotorStop(stick);
		}

		else if(getJoystickValue(BtnEDown) == 1)
		{

			lower();
			setMotorTarget(stick,0,100);
			waitUntilMotorStop(Lift);
			setMotorTarget(Hook,95,100);
			status=0;
			waitUntilMotorStop(stick);
		}



		if(getJoystickValue(BtnFDown) == 1&&status!=0)
		{

			setMotorTarget(stick,220,100);
			waitUntilMotorStop(stick);

		}
		else if(getJoystickValue(BtnFUp) == 1||status==0)
		{
			setMotorTarget(stick,-5,100);
		}
		else
		{
			setMotorSpeed(stick, 0);

		}

		if(getMotorEncoder(stick)<=0){
			setTouchLEDColor(toucharm,colorBlue);
		}
		else{
			setTouchLEDColor(toucharm,colorNone);
		}




		waiting = 0;
		if(getJoystickValue(BtnLUp) == 1) {
			startTask(raise);
			waiting = 1;
			status = 2;

			waitUntil(getMotorEncoder(Lift)>3*armencoder/5)

			if (disablestick){

				setMotorTarget(stick,220,100);
			}
			waitUntil(getJoystickValue(BtnLUp)==0);
			waitUntilMotorStop(stick);
			setTouchLEDColor(toucharm,colorRed);
		}
		else if(getJoystickValue(BtnLDown) == 1 && waiting==0)
		{
			if (status==2){

				setMotorTarget(stick,220,100);
				//wait until the stick releases
				setMotorTarget(Lift,armencoder-150.0,100);
				waitUntil(getMotorEncoder(Lift)<armencoder-130);
				setMotorTarget(hook,95,100);
				status=1;
				waiting=1;
				waitUntilMotorStop(stick);
				waitUntilMotorStop(Lift);
				setTouchLEDColor(toucharm,colorOrange);
				disablestick=false;
			}
			if (status==1 && waiting==0){
				status=0;
				setmotortarget(stick,0,100);
				lower();
				setTouchLEDColor(toucharm,colorYellow);
				disablestick=True;
			}
			waitUntil(getJoystickValue(BtnLDown)==0);
		}

		/*
		if(getJoystickValue(BtnLUp) == 1 && getBumperValue(bumper)==0) {
		setMotorSpeed(Lift,100);
		}
		else if(getJoystickValue(BtnLDown) == 1 && getMotorEncoder(Lift)!=0)
		{
		setMotorSpeed(Lift,-100);
		}
		else{
		setMotorSpeed(Lift,0);
		}
		*/


		eraseUserScreenArea();
		LiftH=getMotorEncoder(Lift);
		gyrovalue=getGyroDegreesFloat(gyro);
		displayTextLine(1, "Heading: %d",  gyrovalue);
		displayTextLine(2, "Arm Height: %d",  LiftH);
		displayTextLine(3, "Claw: %d",  getMotorEncoder(stick));
		//setTouchLEDColor(toucharm,colorBlue);

	}
}
