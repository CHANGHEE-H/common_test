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
    static void printExitMessage() { printf("���̹���\n"); }
    static void printTestLoading() { printf("Test...\n"); }
    static void printSelectionFormatError() { printf("ERROR :: ���ڸ� �Է� ����\n"); }
    static void printUnavailableCar() { printf("�ڵ����� ���۵��� �ʽ��ϴ�\n"); }

    static void printUnavailableEngine() {
        printf("������ ���峪�ֽ��ϴ�.\n");
        printf("�ڵ����� �������� �ʽ��ϴ�.\n");
    }
    static void printAvailableCar(CombinedCar combinedCar) {
        printf("Car Type : %s\n", combinedCar.getCarTypeName().c_str());
        printf("Engine : %s\n", combinedCar.getEngineName().c_str());
        printf("Brake System : %s\n", combinedCar.getBrakeSystemName().c_str());
        printf("SteeringSystem : %s\n", combinedCar.getSteeringSystemName().c_str());

        printf("�ڵ����� ���۵˴ϴ�.\n");
    }
    static void printTestPass() { printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n"); }
    static void printTestFail(std::string reason) {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
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
        printf("� ���� Ÿ���� �����ұ��?\n");

        const std::vector<std::string> carTypes = CarType::getInstance().getCarTypes();

        for (int i = 0; i < carTypes.size(); i++) {
            printf("%d. %s\n", i+1, carTypes[i].c_str());
        }
    } 

    static void printMenuEngine() {
        printf("� ������ ž���ұ��?\n");
        printf("0. �ڷΰ���\n");

        const std::vector<std::string> Engines = Engine::getInstance().getEngines();

        for (int i = 0; i < Engines.size(); i++) {
            printf("%d. %s\n", i + 1, Engines[i].c_str());
        }
    }

    static void printMenuBrakeSystem() {
        printf("� ������ġ�� �����ұ��?\n");
        printf("0. �ڷΰ���\n");

        const std::vector<std::string> brakeSystems = BrakeSystem::getInstance().getBrakeSystems();

        for (int i = 0; i < brakeSystems.size(); i++) {
            printf("%d. %s\n", i + 1, brakeSystems[i].c_str());
        }
    }

    static void printMenuSteeringSystem() {
        printf("� ������ġ�� �����ұ��?\n");
        printf("0. �ڷΰ���\n");

        const std::vector<std::string> steeringSystems = SteeringSystem::getInstance().getSteeringSystem();

        for (int i = 0; i < steeringSystems.size(); i++) {
            printf("%d. %s\n", i + 1, steeringSystems[i].c_str());
        }
    }

    static void printMenuAction() {
        printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
        printf("� ������ �ұ��?\n");
        printf("0. ó�� ȭ������ ���ư���\n");
        printf("1. RUN\n");
        printf("2. Test\n");
    }

    static void selectCarType(int answer) { printf("���� Ÿ������ %s�� �����ϼ̽��ϴ�.\n", CarType::getInstance().getCarTypeName(answer).c_str()); }
    static void selectEngine(int answer) { printf("%s ������ �����ϼ̽��ϴ�.\n", Engine::getInstance().getEngineName(answer).c_str()); }
    static void selectbrakeSystem(int answer) { printf("%s ������ġ�� �����ϼ̽��ϴ�.\n", BrakeSystem::getInstance().getBrakeSystemName(answer).c_str()); }
    static void selectSteeringSystem(int answer) { printf("%s ������ġ�� �����ϼ̽��ϴ�.\n", SteeringSystem::getInstance().getSteeringSystemName(answer).c_str()); }

    static void printCarTypeRangeError() {  printf("ERROR :: ���� Ÿ���� 1 ~ %d ������ ���� ����\n", CarType::getInstance().getCarTypeKind()); }
    static void printEngineRangeError() { printf("ERROR :: ������ 1 ~ %d ������ ���� ����\n", Engine::getInstance().getEngineKind()); }
    static void printBrakeSystemRangeError() { printf("ERROR :: ������ġ�� 1 ~ %d ������ ���� ����\n", BrakeSystem::getInstance().getBrakeSystemKind()); }
    static void printSteeringSystemRangeError() { printf("ERROR :: ������ġ�� 1 ~ %d ������ ���� ����\n", SteeringSystem::getInstance().getSteeringSystemKind()); }
    static void printRunTestRangeError() { printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n"); }
};