#include <sstream>
#include <ROBOTlib.hpp>
using namespace std;

int main()
{
	/// Specify the robot parameters
    ROBOT robby;
    robby.leftWheel.setRadius(0.2);
    robby.rightWheel.setRadius(0.2);
    robby.leftMotor.setKB(0.1);
    robby.rightMotor.setKB(0.1);
    robby.chassis.setHeight(1);
    robby.chassis.setWidth(5);
    robby.chassis.setLength(3);

	std::vector <vector<string>>data;
	std::string filenameNautilus=("/home/viki/temp/robotMotionController/app/plannedPathText.txt");
	std::ifstream fileIN;


	if(fileIN.is_open())
	{
		std::cout << "ERROR: File Open" << '\n';
		fileIN.close();
		fileIN.open(filenameNautilus.c_str());
	}else{
		fileIN.open(filenameNautilus.c_str());
	};

    std::string x,y,T,t;
	path p;

	while(fileIN.good()){
		getline(fileIN,x,',');
		getline(fileIN,y,',');
		getline(fileIN,T,',');
		getline(fileIN,t,'\n');

		p.x.push_back(strtod(x.c_str(),NULL));
		p.y.push_back(strtod(y.c_str(),NULL));
		p.theta.push_back(strtod(T.c_str(),NULL));
		p.time.push_back(strtod(t.c_str(),NULL));
	}
	fileIN.close();
    std::vector<double> speedLeftVec;
    std::vector<double> speedRightVec;
    for(unsigned i=0;i<p.x.size()-2;i++){
    	double dx=p.x[i+1]-p.x[i];
    	double dy=p.y[i+1]-p.y[i];
    	double dT=p.theta[i+1]-p.theta[i];
    	double dt=p.time[i+1]-p.time[i];
    	double T=p.theta[i];
    	double x=p.x[i];
    	double y=p.y[i];

    	struct angularVelocity aV = robby.forwardKinematics(dx,dy,dT,x,y,T,dt);
    	cout << "Left Wheel Velocity " << round(aV.left) << "  :  Right Wheel Velocity " << round(aV.right) << "\n";
    };

    return 0;
}
