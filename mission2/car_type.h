#pragma once
#include <string>
#include <vector>


class CarType {
public:
    enum CarType_E {
        SEDAN,
        SUV,
        TRUCK
    };

    static CarType& getInstance();
    const std::vector<std::string> getCarTypes();
    std::string getCarTypeName(int carType);
    int getCarTypeKind();

private:
    CarType() {}
    ~CarType() {}

    const std::vector<std::string> m_carTypeStr = { "Sedan", "SUV", "Truck"};
};