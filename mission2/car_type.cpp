#include "car_type.h"

CarType& CarType::getInstance() {
    static CarType instance;
    return instance;
}
const std::vector<std::string> CarType::getCarTypes() {
    return m_carTypeStr;
}

std::string CarType::getCarTypeName(int carType) {
    return m_carTypeStr[carType];
}

int CarType::getCarTypeKind() {
    return (int)m_carTypeStr.size();
}