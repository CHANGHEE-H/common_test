#include "combined_car.h"

void CombinedCar::setCarType(int carType) { m_carType = carType; }
void CombinedCar::setEngine(int engine) { m_engine = engine; }
void CombinedCar::setBrakeSystem(int brakeSystem) { m_brakeSystem = brakeSystem; }
void CombinedCar::setSteeringSystem(int steeringSystem) { m_steeringSystem = steeringSystem; }

int CombinedCar::getCarType() { return m_carType; }
int CombinedCar::getEngine() { return m_engine; }
int CombinedCar::getBrakeSystem() { return m_brakeSystem; }
int CombinedCar::getSteeringSystem() { return m_steeringSystem; }

std::string CombinedCar::getCarTypeName() { return CarType::getInstance().getCarTypeName(m_carType); }
std::string CombinedCar::getEngineName() { return Engine::getInstance().getEngineName(m_engine); }
std::string CombinedCar::getBrakeSystemName() { return BrakeSystem::getInstance().getBrakeSystemName(m_brakeSystem); }
std::string CombinedCar::getSteeringSystemName() { return SteeringSystem::getInstance().getSteeringSystemName(m_steeringSystem); }
