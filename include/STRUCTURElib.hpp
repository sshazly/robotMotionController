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
using namespace std;

struct angularVelocity {
	double left;
	double right;
};

struct path {
	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> theta;
	std::vector<double> time;
};
