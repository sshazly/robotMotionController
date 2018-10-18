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
#include <iostream>
#include <fstream>
using namespace std;

/// Define wheel with radius
class WHEEL {
public:
	void setRadius(double _r);
	double getRadius();
	WHEEL();
private:
	double radius;
};


/// subfunction to set the private radius
void WHEEL::setRadius(double _r) {
	this->radius = _r;
}

/// subfunction to get the private gain variable Ki
double WHEEL::getRadius() {
	return (radius);
}
/// Class constructor
WHEEL::WHEEL(void){
  cout << "Object is being created" << endl;
}
