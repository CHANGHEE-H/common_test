#include "combined_car.h"

class TestExecutor {
public:
    static TestExecutor& getInstance() {
        static TestExecutor instance;
        return instance;
    }

    bool isValidCheck(CombinedCar combinedCar) {
        if (
            true == isSedanAndContinental(combinedCar) ||
            true == isSUVAndToyota(combinedCar) ||
            true == isTruckAndWia(combinedCar) ||
            true == isTruckAndMando(combinedCar) ||
            false == isBoschSteeringForBoschBrake(combinedCar)
            ) {
            return false;
        }

        return true;
    }

    std::string getInvalidComponent(CombinedCar combinedCar) {
        std::string ret;
        if (true == isSedanAndContinental(combinedCar)) {
            ret = "Sedan���� Continental������ġ ��� �Ұ�";
        }
        else if (true == isSUVAndToyota(combinedCar)) {
            ret = "SUV���� TOYOTA���� ��� �Ұ�";
        }
        else if (true == isTruckAndWia(combinedCar)) {
            ret = "Truck���� WIA���� ��� �Ұ�";
        }
        else if (true == isTruckAndMando(combinedCar)) {
            ret = "Truck���� Mando������ġ ��� �Ұ�";
        }
        else if (false == isBoschSteeringForBoschBrake(combinedCar)) {
            ret = "Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�";
        }

        return ret;
    }

private:
    TestExecutor() {}

    bool isBoschSteeringForBoschBrake(CombinedCar combinedCar) {
        bool ret = true;
        if (BrakeSystem::BOSCH_B != combinedCar.getBrakeSystem()) {
            ret = true;
        }
        else if (SteeringSystem::BOSCH_S != combinedCar.getSteeringSystem()) {
            ret = false;
        }

        return ret;
    }

    bool isTruckAndMando(CombinedCar combinedCar) {
        return combinedCar.getCarType() == CarType::TRUCK && combinedCar.getBrakeSystem() == BrakeSystem::MANDO;
    }

    bool isTruckAndWia(CombinedCar combinedCar) {
        return combinedCar.getCarType() == CarType::TRUCK && combinedCar.getEngine() == Engine::WIA;
    }

    bool isSUVAndToyota(CombinedCar combinedCar) {
        return combinedCar.getCarType() == CarType::SUV && combinedCar.getEngine() == Engine::TOYOTA;
    }

    bool isSedanAndContinental(CombinedCar combinedCar) {
        return combinedCar.getCarType() == CarType::SEDAN && combinedCar.getBrakeSystem() == BrakeSystem::CONTINENTAL;
    }

};