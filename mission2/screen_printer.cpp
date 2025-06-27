#include "combined_car.h"

#define CLEAR_SCREEN "\033[H\033[2J"

enum MenuType {
    MenuCarType,
    MenuEngine,
    MenuBrakeSystem,
    MenuSteeringSystem,
    MenuRunTest,
};

class ScreenPrinter {
public:
    static void printMenu(int step) {
        printf(CLEAR_SCREEN);

        if (step == MenuCarType) {
            printMenuCarType();
        }
        else if (step == MenuEngine) {
            printMenuEngine();
        }
        else if (step == MenuBrakeSystem) {
            printMenuBrakeSystem();
        }
        else if (step == MenuSteeringSystem) {
            printMenuSteeringSystem();
        }
        else if (step == MenuRunTest) {
            printMenuAction();
        }
    }

    static void printSelection(int answer, int step) {
        if (step == MenuCarType) {
            selectCarType(answer);
        }
        else if (step == MenuEngine) {
            selectEngine(answer);
        }
        else if (step == MenuBrakeSystem) {
            selectbrakeSystem(answer);
        }
        else if (step == MenuSteeringSystem) {
            selectSteeringSystem(answer);
        }
    }

    static void printSelectionRangeError(int step) {
        if (step == MenuCarType) {
            printCarTypeRangeError();
        }
        else if (step == MenuEngine) {
            printEngineRangeError();
        }
        else if (step == MenuBrakeSystem) {
            printBrakeSystemRangeError();
        }
        else if (step == MenuSteeringSystem) {
            printSteeringSystemRangeError();
        }
        else if (step == MenuRunTest) {
            printRunTestRangeError();
        }
    }

    static void printInputLoading() { printf("===============================\nINPUT > "); }
    static void printExitMessage() { printf("바이바이\n"); }
    static void printTestLoading() { printf("Test...\n"); }
    static void printSelectionFormatError() { printf("ERROR :: 숫자만 입력 가능\n"); }
    static void printUnavailableCar() { printf("자동차가 동작되지 않습니다\n"); }

    static void printUnavailableEngine() {
        printf("엔진이 고장나있습니다.\n");
        printf("자동차가 움직이지 않습니다.\n");
    }
    static void printAvailableCar(CombinedCar combinedCar) {
        printf("Car Type : %s\n", combinedCar.getCarTypeName().c_str());
        printf("Engine : %s\n", combinedCar.getEngineName().c_str());
        printf("Brake System : %s\n", combinedCar.getBrakeSystemName().c_str());
        printf("SteeringSystem : %s\n", combinedCar.getSteeringSystemName().c_str());

        printf("자동차가 동작됩니다.\n");
    }
    static void printTestPass() { printf("자동차 부품 조합 테스트 결과 : PASS\n"); }
    static void printTestFail(std::string reason) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("%s\n", reason.c_str());
    }
private:
    static void printMenuCarType() {
        printf("        ______________\n");
        printf("       /|            | \n");
        printf("  ____/_|_____________|____\n");
        printf(" |                      O  |\n");
        printf(" '-(@)----------------(@)--'\n");
        printf("===============================\n");
        printf("어떤 차량 타입을 선택할까요?\n");

        const std::vector<std::string> carTypes = CarType::getInstance().getCarTypes();

        for (int i = 0; i < carTypes.size(); i++) {
            printf("%d. %s\n", i+1, carTypes[i].c_str());
        }
    } 

    static void printMenuEngine() {
        printf("어떤 엔진을 탑재할까요?\n");
        printf("0. 뒤로가기\n");

        const std::vector<std::string> Engines = Engine::getInstance().getEngines();

        for (int i = 0; i < Engines.size(); i++) {
            printf("%d. %s\n", i + 1, Engines[i].c_str());
        }
    }

    static void printMenuBrakeSystem() {
        printf("어떤 제동장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");

        const std::vector<std::string> brakeSystems = BrakeSystem::getInstance().getBrakeSystems();

        for (int i = 0; i < brakeSystems.size(); i++) {
            printf("%d. %s\n", i + 1, brakeSystems[i].c_str());
        }
    }

    static void printMenuSteeringSystem() {
        printf("어떤 조향장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");

        const std::vector<std::string> steeringSystems = SteeringSystem::getInstance().getSteeringSystem();

        for (int i = 0; i < steeringSystems.size(); i++) {
            printf("%d. %s\n", i + 1, steeringSystems[i].c_str());
        }
    }

    static void printMenuAction() {
        printf("멋진 차량이 완성되었습니다.\n");
        printf("어떤 동작을 할까요?\n");
        printf("0. 처음 화면으로 돌아가기\n");
        printf("1. RUN\n");
        printf("2. Test\n");
    }

    static void selectCarType(int answer) { printf("차량 타입으로 %s을 선택하셨습니다.\n", CarType::getInstance().getCarTypeName(answer).c_str()); }
    static void selectEngine(int answer) { printf("%s 엔진을 선택하셨습니다.\n", Engine::getInstance().getEngineName(answer).c_str()); }
    static void selectbrakeSystem(int answer) { printf("%s 제동장치를 선택하셨습니다.\n", BrakeSystem::getInstance().getBrakeSystemName(answer).c_str()); }
    static void selectSteeringSystem(int answer) { printf("%s 조향장치를 선택하셨습니다.\n", SteeringSystem::getInstance().getSteeringSystemName(answer).c_str()); }

    static void printCarTypeRangeError() {  printf("ERROR :: 차량 타입은 1 ~ %d 범위만 선택 가능\n", CarType::getInstance().getCarTypeKind()); }
    static void printEngineRangeError() { printf("ERROR :: 엔진은 1 ~ %d 범위만 선택 가능\n", Engine::getInstance().getEngineKind()); }
    static void printBrakeSystemRangeError() { printf("ERROR :: 제동장치는 1 ~ %d 범위만 선택 가능\n", BrakeSystem::getInstance().getBrakeSystemKind()); }
    static void printSteeringSystemRangeError() { printf("ERROR :: 조향장치는 1 ~ %d 범위만 선택 가능\n", SteeringSystem::getInstance().getSteeringSystemKind()); }
    static void printRunTestRangeError() { printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n"); }
};