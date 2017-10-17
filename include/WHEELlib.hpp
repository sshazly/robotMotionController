/************************************************************
 *                                                          *
 * Copyright (C) 2017 by Sherif Shazly                      *
 *                                                          *
 ***********************************************************/

/**
 *   @file	WHEELlib.hpp
 *   @brief  	This is the main file to define wheel sizes
 *      
 *
 *
 *   @author    Sherif Shazly
 *   @date	2017/10/17
 *  @copyright Copyright (C) 2017 by Sherif Shazly
 *  @bug No known bugs.
 */

#pragma once

/// Define the PID class with variable kp, kd, ki
class WHEEL {
public:
	void setRadius(double _r);
	double getRadius();
private:
	double radius;
};

/// subfunction to set the private gain variables
void WHEEL::setRadius(double _r) {
	this->radius = _r;
}

/// subfunction to get the private gain variable Ki
double WHEEL::getRadius() {
	return (radius);
}

