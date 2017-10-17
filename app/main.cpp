#include <iostream>
#include <ROBOTlib.hpp>

int main()
{
	/// Specify the robot parameters
    ROBOT robby;
    robby.leftWheel.setRadius(0.2);
    robby.rightWheel.setRadius(0.2);
    robby.leftMotor.setKB(0.1);
    robby.rightMotor.setKB(0.1);
    robby.chassis.setHeight(1);
    robby.chassis.setWidth(1);
    robby.chassis.setLength(1);

    struct path p=robby.importPath();
    std::vector<double> speedLeftVec;
    std::vector<double> speedRightVec;
    for(int i=0;i<p.x.size();i++){
    	double dx=p.x(i+1)-p.x(i);
    	double dy=p.y(i+1)-p.y(i);
    	double dT=p.theta(i+1)-p.theta(i);
    	double dt=p.time(i+1)-p.time(i);
    	double T=p.theta(i);

    	struct angularVelocity aV = robby.forwardKinematics(dx,dy,dT,T,dt);
    	cout << "Left Wheel Velocity " << aV.left << "  :  Right Wheel Velocity" << aV.right << "\n";
    };

    return 0;
}
