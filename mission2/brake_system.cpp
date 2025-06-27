#include "brake_system.h"

BrakeSystem& BrakeSystem::getInstance() {
    static BrakeSystem instance;
    return instance;
}

const std::vector<std::string> BrakeSystem::getBrakeSystems() {
    return m_brakeSystemStr;
}

std::string BrakeSystem::getBrakeSystemName(int brakeSystem) {
    return m_brakeSystemStr[brakeSystem];
}

int BrakeSystem::getBrakeSystemKind() {
    return (int)m_brakeSystemStr.size();
}