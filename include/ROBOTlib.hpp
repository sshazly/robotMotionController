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
#include <vector>
///#include <mgl2/mgl.h>
#include <gnuplot_i.hpp>

#include <stdio.h>
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

using namespace std;

/// Define the ROBOT class
class ROBOT {
public:
    ROBOT();
	struct forwardKin forwardKinematics(double dx, double dy, double dT,
			double x, double y, double T, double dt);
	std::vector<double> rot2D(double theta, std::vector<double> vec);
	void simulatePath(std::vector<double> time, std::vector<double> xleft, std::vector<double> yleft, std::vector<double> xright, std::vector<double> yright, std::vector<double> x, std::vector<double> y);
	int sign(double a);
	std::string getDirectory(void);
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

/// Class Constructor
ROBOT::ROBOT(void) {
	ROBOT::ID=1;
	cout << "Object is being created" << endl;
}


/// Determine the left right Motor speeds to reach the next target point
struct forwardKin ROBOT::forwardKinematics(double dx, double dy, double dT,
		double x, double y, double T, double dt) {
	/// Gather Robot Parameters (wheel radius, chassis width)
	double w = chassis.getWidth();
	double rL = leftWheel.getRadius();
	double rR = rightWheel.getRadius();

	// Position of wheels relative to frame
	std::vector <double> pL={-w/2,0};
	std::vector <double> pR={w/2,0};

	/// Create position vector for where the robot wants to go and where it is
	std::vector<double> pos_t0 = {x,y};
	std::vector<double> pos_t1 = {x+dx,y+dy};

	/// Find the position of L/R wheels relative to reference frame at t and t+dt
	/// Rotation and Translation
	std::vector<double> dL_t0 = rot2D(T, pL);
	dL_t0[0]+=pos_t0[0]; // Add x component
	dL_t0[1]+=pos_t0[1]; // Add y component
	std::vector<double> dR_t0 = rot2D(T, pR);
	dR_t0[0]+=pos_t0[0]; // Add x component
	dR_t0[1]+=pos_t0[1]; // Add y component
	std::vector<double> dL_t1 = rot2D(T+dT, pL);
	dL_t1[0]+=pos_t1[0]; // Add x component
	dL_t1[1]+=pos_t1[1]; // Add y component
	std::vector<double> dR_t1 = rot2D(T+dT, pR);
	dR_t1[0]+=pos_t1[0]; // Add x component
	dR_t1[1]+=pos_t1[1]; // Add y component
	/// Populate wheelPosition Structure
	struct forwardKin fK;
	fK.wP.leftX=dL_t0[0];
	fK.wP.leftY=dL_t0[1];
	fK.wP.rightX=dR_t0[0];
	fK.wP.rightY=dR_t0[1];


	/// Find the difference between the wheels position
	/// relative to the reference frame at t and t+dt
	std::vector<double> dLv = {0,0};
	dLv[0]= dL_t1[0]-dL_t0[0]; // x-difference relative to reference frame
	dLv[1]= dL_t1[1]-dL_t0[1]; // y-difference relative to reference frame
	std::vector<double> dRv = {0,0};
	dRv[0]= dR_t1[0]-dR_t0[0];  // x-difference relative to reference frame
	dRv[1]= dR_t1[1]-dR_t0[1];  // y-difference relative to reference frame

	/// Find the new wheel position relative to the old rigid body frame
	/// this will be used in the directional component for angular velocity

	std::vector<double> dL_t1_rel={dL_t1[0],dL_t1[1]}; // Next left wheel position relative to reference frame
	dL_t1_rel[0]+=-x; // Translate left wheel from old position rigid body frame to reference frame
	dL_t1_rel[1]+=-y;
	std::vector<double> dR_t1_rel={dR_t1[0],dR_t1[1]}; // Next right wheel position relative to reference frame
	dR_t1_rel[0]+=-x; // Translate right wheel from old position rigid body frame to reference frame
	dR_t1_rel[1]+=-y;

	/// Rotate vector to be relative to the rigid body frame
	std::vector<double> relL=rot2D(-T,dL_t1_rel);
	std::vector<double> relR=rot2D(-T,dR_t1_rel);

	/// Declare variables for norm calculation
	double power=2.0;
	double dLv0=dLv[0];double dLv1=dLv[1];double dRv0=dRv[0];double dRv1=dRv[0];

	/// Find the norm distance times the magnitude
	double dL = sqrt(pow(dLv0, power) + pow(dLv1, power));
	double dR = sqrt(pow(dRv0, power) + pow(dRv1, power));
	double relL1=relL[1];
	double relR1=relR[1];
	fK.aV.left = dL /dt/rL * sign(relL1);
	fK.aV.right = dR / dt/ rR * sign(relR1);

	return (fK);
}

/// simulate path
void ROBOT::simulatePath(std::vector<double> time, std::vector<double> xleft, std::vector<double> yleft, std::vector<double> xright, std::vector<double> yright, std::vector<double> x, std::vector<double> y) {
	//MathGL plotting
  Gnuplot gp;
  gp.set_style("lines");
  gp.set_xlabel("x");
  gp.set_ylabel("y");
  gp.plot_xy(x,y);
  cout<<"Press Enter to quit...";
  cin.get();

  std::vector<double> x1;
  x1[0]=time[0]+xleft[0]+yleft[0]+xright[0]+yright[0]+x[0]+y[0];

}


std::vector<double> ROBOT::rot2D(double theta, std::vector<double> vec) {
	std::vector<double> vecR = {0,0};
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

std::string ROBOT::getDirectory(void) {
  char buff[FILENAME_MAX];
  GetCurrentDir(buff,FILENAME_MAX);
  std::string current_working_dir(buff);
  return (current_working_dir);
}
