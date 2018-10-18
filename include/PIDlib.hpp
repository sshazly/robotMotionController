/************************************************************
 *                                                          *
 * Copyright (C) 2017 by Sherif Shazly                      *
 *                                                          *
 ***********************************************************/

/**
 *   @file	CHASSISlib.hpp
 *   @brief  	This is the main file to run the PID controller
 *      
 *   Run the velocity controller
 *
 *   @author    Sherif Shazly
 *   @date	2017/3/19
 *  @copyright Copyright (C) 2017 by Sherif Shazly
 *  @bug No known bugs.
 */

#pragma once
#include<iostream>
#include <cmath>
using namespace std;

// Define the PID class with variable kp, kd, ki
class PID {
public:
	void setGain(double _kp, double _ki, double _kd);
	double getKi();
	double getKp();
	double getKd();
	double calculate(double setpoint, double pv);
	void initialize(double _dt);
	PID();
private:
	double kp;					///<kp
	double kd;					///<ki
	double ki;					///<kd
	double preError;                                ///< previous error
	double integral;                             ///< previous integral
	double dt;
};

/// Class constructor
PID::PID(void){
	cout << "Object is being created" << endl;
}

// subfunction to set the private gain variables
void PID::setGain(double _kp, double _ki, double _kd) {
	this->kp = _kp;
	this->ki = _ki;
	this->kd = _kd;
}

// subfunction to initialize the PID controller
void PID::initialize(double _dt) {
	this->dt = _dt;
	this->integral = 0;
	this->preError = 0;
}

// subfunction to get the private gain variable Ki
double PID::getKi() {
	return (ki);
}

// subfunction to get the private gain variable Kp
double PID::getKp() {
	return (kp);
}

// subfunction to get the private gain variable Kd
double PID::getKd() {
	return (kd);
}

// subfunction to calculate the increment neccessary to converge previous value (pv) to setpoint
double PID::calculate(double setpoint, double pv) {
	//double output = setpoint - pv ;

	// Calculate error
	double error = setpoint - pv;

	// Proportional term
	double Pout = kp * error;

	// Integral term
	integral += error * dt;
	double Iout = ki * integral;

	// Derivative term
	double derivative = (error - preError) / dt;
	double Dout = kd * derivative;

	// Calculate total output
	double output = Pout + Iout + Dout;

	// Save error to previous error
	preError = error;

	return (output);
}

