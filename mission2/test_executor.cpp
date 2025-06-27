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
            ret = "Sedan에는 Continental제동장치 사용 불가";
        }
        else if (true == isSUVAndToyota(combinedCar)) {
            ret = "SUV에는 TOYOTA엔진 사용 불가";
        }
        else if (true == isTruckAndWia(combinedCar)) {
            ret = "Truck에는 WIA엔진 사용 불가";
        }
        else if (true == isTruckAndMando(combinedCar)) {
            ret = "Truck에는 Mando제동장치 사용 불가";
        }
        else if (false == isBoschSteeringForBoschBrake(combinedCar)) {
            ret = "Bosch제동장치에는 Bosch조향장치 이외 사용 불가";
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