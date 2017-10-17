/************************************************************
 *                                                          *
 * Copyright (C) 2017 by Sherif Shazly                      *
 *                                                          *
 ***********************************************************/

/** @file test.cpp
 *  @brief Unit tests for motion controller software
 *
 *  This contains multiple tests for all the class subfunctions
 *
 *  The next tests are used to verify the get and set methods work for the
 *
 *  @author Sherif Shazly (sshazly)
 *  @copyright (C) 2017 by Sherif Shazly
 *  @bug
 */

#include <gtest/gtest.h>
#include <CHASSISlib.hpp>
#include <MOTORlib.hpp>
#include <PIDlib.hpp>
#include <SENSORlib.hpp>
#include <WHEELlib.hpp>
/// test (chassis.setHeight)
TEST(setChassisDimensions, should_pass_height) {
	CHASSIS chassis;
	chassis.setHeight(1);
	double H = chassis.getHeight();
	EXPECT_EQ(1, H);
}


/// test (chassis.setWidth)
TEST(setChassisDimensions, should_pass_width) {
	CHASSIS chassis;
	chassis.setWidth(1);
	double W = chassis.getWidth();
	EXPECT_EQ(1, W);
}


/// test (chassis.setLength)
TEST(setChassisDimensions, should_pass_length) {
	CHASSIS chassis;
	chassis.setLength(1);
	double L = chassis.getLength();
	EXPECT_EQ(1, L);
}


/// test (motor.setKT)
TEST(setMotorTorqueConstant, should_pass_torque) {
	MOTOR motor;
	motor.setKT(1);
	double KT = motor.getKT();
	EXPECT_EQ(1, KT);
}


/// test (motor.setKB)
TEST(setMotorVelocityConstant, should_pass_velocity) {
	MOTOR motor;
	motor.setKB(1);
	double KB = motor.getKB();
	EXPECT_EQ(1, KB);
}


/// test (motor.maxV)
TEST(setMotorMaxVoltage, should_pass_voltage) {
	MOTOR motor;
	motor.setMaxV(1);
	double V = motor.getMaxV();
	EXPECT_EQ(1, V);
}


/// test (motor.maxI)
TEST(setMotorMaxCurrent, should_pass_current) {
	MOTOR motor;
	motor.setMaxI(1);
	double V = motor.getMaxI();
	EXPECT_EQ(1, V);
}


/// test (Ki): pid.getKi()=pid.setGain(Kp,Ki,Kd) [the Ki value]
TEST(setGainMethod, should_pass_ki) {
	PID pid;
	pid.setGain(0, 0, 0);
	double ki = pid.getKi();
	EXPECT_EQ(0, ki);
}


/// test (Kp): pid.getKp()=pid.setGain(Kp,Ki,Kd) [the Kp value]
TEST(setGainMethod, should_pass_kp) {
	PID pid;
	pid.setGain(0, 0, 0);
	double kp = pid.getKp();
	EXPECT_EQ(0, kp);
}


/// test (Kd): pid.getKi()=pid.setGain(Kp,Ki,Kd) [the Kd value]
TEST(setGainMethod, should_pass_kd) {
	PID pid;
	pid.setGain(0, 0, 0);
	double kd = pid.getKd();
	EXPECT_EQ(0, kd);
}


/// Proximity sensor set/get sensitivity
TEST(setProximitySensorSensitivity, should_pass_sensitivity) {
	PROXIMITY prox;
	prox.setSensitivity(1);
	double s = prox.getSensitivity();
	EXPECT_EQ(1, s);
}


/// Wheel set/get radius
TEST(setWheelRadius, should_pass_radius) {
	WHEEL wheel;
	wheel.setRadius(1);
	double r = wheel.getRadius();
	EXPECT_EQ(1, r);
}


