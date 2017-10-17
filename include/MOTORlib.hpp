/************************************************************
 *                                                          *
 * Copyright (C) 2017 by Sherif Shazly                      *
 *                                                          *
 ***********************************************************/

/**
 *   @file	MOTORlib.hpp
 *   @brief  	This is the main file to run the PID controller
 *      
 *   Run the velocity controller
 *
 *   @author    Sherif Shazly
 *   @date	2017/10/17
 *  @copyright Copyright (C) 2017 by Sherif Shazly
 *  @bug No known bugs.
 */

#pragma once

/// Define the MOTOR class with variable kT, kV
class MOTOR {
public:
	void setSpeed(double _speed);
	double getKT();
	double getKB();
	double getMaxV();
	double getMaxI();
	void setKT(double _kT);
	void setKB(double _kB);
	void setMaxV(double _maxV);
	void setMaxI(double _maxI);
private:
	double kT;					///<kT torque/current constant
	double kB;					///<kB speed/voltage constant
	double speed;					///<speed [rad/sec]
	double maxV;					///<max Voltage [Volts]
	double maxI;					///<max current [Amperes]

};

/// subfunction to set the torque/current constant
void MOTOR::setKT(double _kT) {
	this->kT = _kT;
}

/// subfunction to set the speed/voltage constant
void MOTOR::setKB(double _kB) {
	this->kB = _kB;
}

/// subfunction to set the max voltage
void MOTOR::setMaxV(double _maxV) {
	this->maxV = _maxV;
}

/// subfunction to set the max current
void MOTOR::setMaxI(double _maxI) {
	this->maxI = _maxI;
}

/// subfunction to set the torque/current constant
double MOTOR::getKT() {
	return (kT);
}

/// subfunction to set the speed/voltage constant
double MOTOR::getKB() {
	return (kB);
}

/// subfunction to set the max voltage
double MOTOR::getMaxV() {
	return (maxV);
}

/// subfunction to set the max current
double MOTOR::getMaxI() {
	return (maxI);
}

void MOTOR::setSpeed(double _speed) {
	this->speed = _speed;
}

