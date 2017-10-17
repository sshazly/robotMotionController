/************************************************************
 *                                                          *
 * Copyright (C) 2017 by Sherif Shazly                      *
 *                                                          *
 ***********************************************************/

/**
 *   @file	ROBOTlib.hpp
 *   @brief  	This is the robot class which houses the ID and forward/inverse kinematic models
 *      
 *   forward kinematics maps the change in position/orientation to right/left wheel differentials
 *   @author    Sherif Shazly
 *   @date	2017/10/17
 *   @copyright Copyright (C) 2017 by Sherif Shazly
 *   @bug No known bugs.
 */

#pragma once
#include <iostream>
#include <cmath>
#include <math.h>
#include <SENSORlib.hpp>
#include <WHEELlib.hpp>
#include <PIDlib.hpp>
#include <CHASSISlib.hpp>
#include <MOTORlib.hpp>
#include <STRUCTURElib.hpp>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

/// Define the ROBOT class
class ROBOT {
public:
	struct angularVelocity forwardKinematics(double dx, double dy, double dT,
			double T, double dt);
	std::vector<double> rot2D(double theta, std::vector<double> vec);
	void simulatePath();
	struct path importPath();
	int sign(double a);
	WHEEL leftWheel;
	WHEEL rightWheel;
	MOTOR leftMotor;
	MOTOR rightMotor;
	CHASSIS chassis;
	PROXIMITY sensorLeft;
	PROXIMITY sensorRight;
	PROXIMITY sensorForward;
	PROXIMITY sensorBackward;

private:
	int ID;					///<Specific robot ID
};

/// Determine the left right Motor speeds to reach the next target point
struct angularVelocity ROBOT::forwardKinematics(double dx, double dy, double dT,
		double T, double dt) {
	/// Gather Robot Parameters (wheel radius, chassis width)
	double w = chassis.getWidth();
	double rL = leftWheel.getRadius();
	double rR = rightWheel.getRadius();
	/// Create position vector for where the robot wants to go
	std::vector<double> pos;
	pos[0] = dx;
	pos[1] = dy;

	/// Find the projection of the instantaneous velocity on the chassis frame
	std::vector<double> posrel = rot2D(T, pos);

	/// Find the
	double d = sqrt(pow(dx, 2.0) + pow(dy, 2.0));
	angularVelocity aV;
	int fD = sign(posrel[1]);
	if (dT != 0) {
		double curv = d / 2 / (sin(dT / 2));
		double c1 = curv * fD + w / 2;
		double c2 = curv * fD - w / 2;
		aV.left = c1 * dT / dt / rL;
		aV.right = c2 * dT / dt / rR;
	} else {
		aV.left = d / dt / rL;
		aV.right = d / dt / rR;
	};

	return (aV);
}

/// simulate path
void ROBOT::simulatePath() {
	//std::vector<double> wheelSpeeds[0]=0;
}

/// import path planner file
struct path ROBOT::importPath() {
	path p;
	p.x[0] = 1;
	p.y[0] = 1;
	p.theta[0] = 1;
	p.time[0] = 1;

	return p;
}

std::vector<double> ROBOT::rot2D(double theta, std::vector<double> vec) {
	std::vector<double> vecR;
	vecR[0] = cos(theta) * vec[0] - sin(theta) * vec[1];
	vecR[1] = sin(theta) * vec[0] + cos(theta) * vec[1];
	return (vecR);
}

int ROBOT::sign(double a) {
	if (a >= 0) {
		return (1);
	} else {
		return (-1);
	};
	return (0);
}

