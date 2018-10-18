/************************************************************
 *                                                          *
 * Copyright (C) 2017 by Sherif Shazly                      *
 *                                                          *
 ***********************************************************/

/**
 *   @file	SENSORlib.hpp
 *   @brief  	This is the main file containing class sensor and subclass sensors
 *      
 *   Run the velocity controller
 *
 *   @author    Sherif Shazly
 *   @date	2017/10/17
 *  @copyright Copyright (C) 2017 by Sherif Shazly
 *  @bug No known bugs.
 */

#pragma once
#include <iostream>
#include <fstream>
using namespace std;

/// Define the PID class with variable kp, kd, ki
class SENSOR {
public:
	void turnOn();
	void turnOff();
	SENSOR();

private:
	bool isOn;

};

/// Class constructor
SENSOR::SENSOR(void){
	cout << "Object is being created" << endl;
}

/// subfunction to set the private gain variables
void SENSOR::turnOn() {
	this->isOn = true;
}
void SENSOR::turnOff() {
	this->isOn = false;
}

class PROXIMITY: SENSOR {
public:
	void setSensitivity(double voltage);
	double getSensitivity();
	bool alert();
private:
	double sensorReading;
	double voltageSensitivity;
};

void PROXIMITY::setSensitivity(double voltage) {
	this->voltageSensitivity = voltage;
}

double PROXIMITY::getSensitivity() {
	return (voltageSensitivity);
}

bool PROXIMITY::alert() {
	return (sensorReading > voltageSensitivity);
}

