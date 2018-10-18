/************************************************************
 *                                                          *
 * Copyright (C) 2017 by Sherif Shazly                      *
 *                                                          *
 ***********************************************************/

/**
 *   @file	STRUCTURElib.hpp
 *   @brief  	This header file contains structure definitions used by the path planner
 *   			and the
 *
 *   @author    Sherif Shazly
 *   @date	2017/10/17
 *  @copyright Copyright (C) 2017 by Sherif Shazly
 *  @bug No known bugs.
 */
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct forwardKin {
	struct angularVelocity {
		double left;
		double right;
	};
	angularVelocity aV;
	struct wheelPosition {
		double leftX;
		double rightX;
		double leftY;
		double rightY;
	};
	wheelPosition wP;
};

struct path {
	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> theta;
	std::vector<double> time;
};
