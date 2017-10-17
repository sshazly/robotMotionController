/************************************************************
 *                                                          *
 * Copyright (C) 2017 by Sherif Shazly                      *
 *                                                          *
 ***********************************************************/

/**
 *   @file	CHASSISlib.hpp
 *   @brief  	This is the class file for the robot chassis
 *      
 *   Describes the robotic chassis (box which contains the robot)
 *
 *   @author    Sherif Shazly
 *   @date	2017/10/17
 *  @copyright Copyright (C) 2017 by Sherif Shazly
 *  @bug No known bugs.
 */

#pragma once

/// Define the CHASSIS class
class CHASSIS {
public:
	void setHeight(double H);
	void setWidth(double W);
	void setLength(double L);
	double getHeight();
	double getWidth();
	double getLength();
private:
	double height;
	double width;
	double length;
};

/// subfunction to set the private height variable
void CHASSIS::setHeight(double H) {
	this->height = H;
}

/// subfunction to set the private width variable
void CHASSIS::setWidth(double W) {
	this->width = W;
}

/// subfunction to set the private length variable
void CHASSIS::setLength(double L) {
	this->length = L;
}

/// subfunction to get the private width variable
double CHASSIS::getWidth() {
	return (width);
}

/// subfunction to get the private height variable
double CHASSIS::getHeight() {
	return (height);
}

/// subfunction to get the private length variable
double CHASSIS::getLength() {
	return (length);
}
