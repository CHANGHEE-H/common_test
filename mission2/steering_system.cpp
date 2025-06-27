#include "steering_system.h"

SteeringSystem& SteeringSystem::getInstance() {
    static SteeringSystem instance;
    return instance;
}

const std::vector<std::string> SteeringSystem::getSteeringSystem() {
    return m_steeringSystemStr;
}

std::string SteeringSystem::getSteeringSystemName(int steeringSystem) {
    return m_steeringSystemStr[steeringSystem];
}

int SteeringSystem::getSteeringSystemKind() {
    return (int)m_steeringSystemStr.size();
}