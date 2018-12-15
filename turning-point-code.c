#pragma config(Sensor, dgtl1,  quadLeft,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  quadRight,      sensorQuadEncoder)
#pragma config(Motor,  port1,           leftFront,     tmotorVex393HighSpeed_HBridge, openLoop, driveLeft)
#pragma config(Motor,  port2,           descorer,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           leftBack,      tmotorVex393HighSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port4,           rightCenter,   tmotorVex393HighSpeed_MC29, openLoop, driveRight)
#pragma config(Motor,  port5,           leftCenter,    tmotorVex393HighSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port6,           rightBack,     tmotorVex393HighSpeed_MC29, openLoop, driveRight)
#pragma config(Motor,  port7,           linearPunch,   tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           intake,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          rightFront,    tmotorVex393HighSpeed_HBridge, openLoop, driveRight)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define abs(X) ((X < 0) ? -1 * X : X)

// ---------------------------------------------------------------------------------------------- Global Variables
// Additional features (Descorer, Intake, Linear Punch)
string intakeForward = Btn5U;
string intakeBackward = Btn5D;
string puncherGo = Btn6U;
string puncherRetreat = Btn6D;
string descorerOn = Btn7U;
string descorerOff = Btn7D;

// Autonomous
int wheelDiameter = 4;					// Set the wheel diameter in inches; called in encoder functions; use float and 10.16 for cm
int encoderTicks = 360;					// Number of ticks in a revolution; OSE = 360; IEM = 627.2 at 100 rpm gearing; 392 at 160 rpm gearing
int q1, q2, q3, q4;							// Variables to record distances for testing

// Drive
int deadzone = 30;
/*---------------------------------------------------------------------------*/
/*																																					 */
/*				Description: Competition template for VEX EDR											 */
/*																																					 */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*													Pre-Autonomous Functions												 */
/*																																					 */
/*	You may want to perform some actions before the competition starts.			 */
/*	Do them in the following function.	You must return from this function	 */
/*	or the autonomous and usercontrol tasks will not be started.	This			 */
/*	function is only called once after the cortex has been powered on and		 */
/*	not every time that the robot is disabled.															 */
/*---------------------------------------------------------------------------*/
void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

// ---------------------------------------------------------------------------------------------- Drive Functions
// Function to set all drive motors to a specified speed
// Positive speed = forward, negative speed = reverse drive

void autoDrive(int speed)
{
	motor[leftFront] = speed;
	motor[leftCenter] = speed;
	motor[leftBack] = speed;
	motor[rightFront] = -speed;
	motor[rightCenter] = -speed;
	motor[rightBack] = -speed;
}

// Function to run autoDrive for specified mSec then stop the drive motors
void autoDriveTime(int speed, int mSec)
{
	autoDrive(speed);
	wait1Msec(mSec);
	autoDrive(0);
}

//Function to run autoDrive for specified distance
void autoDriveDist(int speed, int dist)
{
	SensorValue(quadLeft) = 0;											// Reset the OSE value to 0
	int ticks = dist/(4*PI) * 360;									// Convert distance into OSE values; wheelDiameter and encoderTicks are set in Global Variables
	while (abs(SensorValue(quadLeft)) < ticks)			// While quadLeft is less ticks, run autoDrive at speed
	{
		autoDrive(speed);
	}
	autoDrive(0);																		// Stop drive motors
}
// ---------------------------------------------------------------------------------------------- Turn Functions


task autonomous()
{
autoDriveDist(90, 60);							// First argument is speed, second argument is distance (how far it travels); number varies accordingly
wait1Msec(1000);										// Waits 1 second before executing the next command
q1 = SensorValue(quadLeft);					// Stating int q1 = quadLeft for testing purposes
autoDriveDist(-20, 60);
wait1Msec(1000);
q2 = SensorValue(quadLeft);
autoDriveDist(20, 60);
wait1Msec(1000);
q3 = SensorValue(quadLeft);
autoDriveDist(-20, 60);
wait1Msec(1000);
q4 = SensorValue(quadLeft);
autoDriveDist(20, 60);
wait1Msec(1000);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


task usercontrol()
{

	while (true)
	{

		if (vexRT(Ch3)> deadzone || vexRT(Ch3)< -deadzone)
		{
			motor[leftBack] = vexRT[Ch3];
			motor[leftFront] = vexRT[Ch3];
			motor[leftCenter] = vexRT[Ch3];

		}
		else
		{
			motor[leftBack] = 0;
			motor[leftFront] = 0;
			motor[leftCenter] = 0;
		}

		if (vexRT(Ch2)> deadzone || vexRT(Ch2)< -deadzone)
		{
			motor[rightBack] = vexRT[Ch2];
			motor[rightFront] = vexRT[Ch2];
			motor[rightCenter] = vexRT[Ch2];

		}
		else
		{
			motor[rightBack] = 0;
			motor[rightFront] = 0;
			motor[rightCenter] = 0;
		}


		if (vexRT[intakeForward] == true)
		{
			motor[intake] = -127;
		}

		else if (vexRT[intakeBackward] == true)
		{
			motor[intake] = 127;

		}

		else
		{
			motor[intake] = 0;
		}

		if (vexRT[puncherGo] == true)
		{
		motor[linearPunch] = 127;
		}

		else if (vexRT[puncherRetreat] == true)
		{
		motor[linearPunch] = 127;
		}

		else
		{
		motor[linearPunch] = 0;
		}
		if (vexRT[descorerOn] == true)
		{
		motor[descorer] = 127;
		}

		else if (vexRT[descorerOff] == true)
		{
		motor[descorer] = -127;
		}

		else
		{
		motor[descorer] = 0;
		}
	}
	}










































































































































































































































































































































































































































































	//sOnNy Is GoD pRoGrAmMeR







		////end time slice...
