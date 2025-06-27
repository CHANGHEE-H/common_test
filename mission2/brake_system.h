#pragma once
#include <string>
#include <vector>

class BrakeSystem {
public:
    enum BrakeSystem_E {
        MANDO,
        CONTINENTAL,
        BOSCH_B
    };

    static BrakeSystem& getInstance();
    const std::vector<std::string> getBrakeSystems();
    std::string getBrakeSystemName(int brakeSystem);
    int getBrakeSystemKind();

private:
    BrakeSystem() {}
    ~BrakeSystem() {}

    const std::vector<std::string> m_brakeSystemStr = { "MANDO", "CONTINENTAL", "BOSCH_B" };

};