#pragma once
#include "car_type.h"
#include "engine.h"
#include "brake_system.h"
#include "steering_system.h"

class CombinedCar {
public:
	void setCarType(int carType);
	void setEngine(int engine);
	void setBrakeSystem(int brakeSystem);
	void setSteeringSystem(int steeringSystem);

	int getCarType();
	int getEngine();
	int getBrakeSystem();
	int getSteeringSystem();

	std::string getCarTypeName();
	std::string getEngineName();
	std::string getBrakeSystemName();
	std::string getSteeringSystemName();

private:
	int m_carType = 0;
	int m_engine = 0;
	int m_brakeSystem = 0;
	int m_steeringSystem = 0;
};