#include <sstream>
#include<iostream>
#include <fstream>
#include <string>
#include <gnuplot_i.hpp>
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
    string file_path = __FILE__;
    string currentDir = file_path.substr(0,file_path.rfind("/"));
	std::vector <vector<string>>data;
	std::string filenameNautilus=currentDir + "/plannedPathText.txt";
	std::ifstream fileIN;


	if(fileIN.is_open())
	{
		std::cout << "ERROR: File Open" << '\n';
		fileIN.close();
		fileIN.open(filenameNautilus.c_str(), std::ifstream::in);
	}else{
		fileIN.open(filenameNautilus.c_str(), std::ifstream::in);
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

    std::vector<double> xLeft;
    std::vector<double> xRight;
    std::vector<double> yLeft;
    std::vector<double> yRight;
    std::vector<double> yVec,xVec;

    vector< vector<double> > allX;
    vector< vector<double> > allY;

    Gnuplot gp;
    gp.set_style("lines");
    gp.set_xlabel("x");
    gp.set_ylabel("y");
    //gp.plot_xy(p.x,p.y);
    for(unsigned i=0;i<p.x.size()-10;i++){
    	double dx=p.x[i+1]-p.x[i];
    	double dy=p.y[i+1]-p.y[i];
    	double dT=p.theta[i+1]-p.theta[i];
    	double dt=p.time[i+1]-p.time[i];
    	double T=p.theta[i];
    	double x=p.x[i];
    	double y=p.y[i];

    	forwardKin fK = robby.forwardKinematics(dx,dy,dT,x,y,T,dt);
    	xLeft.push_back(fK.wP.leftX);
    	xRight.push_back(fK.wP.rightX);
    	yLeft.push_back(fK.wP.leftY);
    	yRight.push_back(fK.wP.rightY);
    	yVec.push_back(p.y[i]);
    	xVec.push_back(p.x[i]);
    	cout << "Left Wheel Velocity " << round(fK.aV.left) << "  :  Right Wheel Velocity " << round(fK.aV.right) << "\n";
    	//gp.remove_tmpfiles();

//    	allX[0][i]=xVec[i];
//    	allX[1][i]=xLeft[i];
//    	allX[2][i]=xRight[i];
//    	allY[0][i]=yVec[i];
//    	allY[1][i]=yLeft[i];
//    	allY[2][i]=yRight[i];
//    	gp.plot_xy_multi(allX,allY,"");
//    	if(i==0){
//    	    //gp.plot_xy(p.x,p.y);
//    	    //gp.plot_xy(xLeft,yLeft);
//    	    //gp.plot_xy(xRight,yRight);
//    	}else{
//    	    //gp.plot_xy(p.x,p.y);
//    	    //gp.plot_xy(xLeft,yLeft);
//    	    //gp.plot_xy(xRight,yRight);
//    	};


    };
	allX.push_back(xVec);
	allX.push_back(xLeft);
	allX.push_back(xRight);
	allY.push_back(yVec);
	allY.push_back(yLeft);
	allY.push_back(yRight);
	gp.plot_xy_multi(allX,allY,"");
//	if(i==0){
//	    //gp.plot_xy(p.x,p.y);
//	    //gp.plot_xy(xLeft,yLeft);
//	    //gp.plot_xy(xRight,yRight);
//	}else{
//	    //gp.plot_xy(p.x,p.y);
//	    //gp.plot_xy(xLeft,yLeft);
//	    //gp.plot_xy(xRight,yRight);
//	};
    cout<<"Press Enter to quit...";
    cin.get();
    return (0);
}
