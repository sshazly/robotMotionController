#include <iostream>
#include <ROBOTlib.hpp>

int main()
{
    ROBOT robby;
    robby.leftWheel.setRadius(0.2);
    robby.rightWheel.setRadius(0.2);
    robby.leftMotor.setKB(0.1);
    robby.rightMotor.setKB(0.1);
    robby.chassis.setHeight(1);
    robby.chassis.setWidth(1);
    robby.chassis.setLength(1);

    return 0;
}
