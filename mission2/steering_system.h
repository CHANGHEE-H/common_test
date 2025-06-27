#pragma once
#include <string>
#include <vector>

class SteeringSystem {
public:
    enum SteeringSystem_E {
        BOSCH_S,
        MOBIS
    };

    static SteeringSystem& getInstance();
    const std::vector<std::string> getSteeringSystem();
    std::string getSteeringSystemName(int steeringSystem);
    int getSteeringSystemKind();

private:
    SteeringSystem() {}
    ~SteeringSystem() {}

    const std::vector<std::string> m_steeringSystemStr = { "BOSCH_S", "MOBIS" };
};