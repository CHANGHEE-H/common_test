#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"
#define DELAY_TIME_FOR_OUTPUT 2000
#define DELAY_FOR_TEST_LOADING 1500

#define TEST_LOADING_MESSAGE "Test...\n"
#define EXIT_COMMAND "exit"
#define EXIT_MESSAGE "���̹���\n"

int userSelection[10];

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);

void printMenu(int step);
void printMenuCarType();
void printMenuEngine();
void printMenuBrakeSystem();
void printMenuSteeringSystem();
void printMenuAction();

void runProducedCar();
void testProducedCar();

void makeDelayOnScreen(int ms);

bool isSedanAndContinental();
bool isSUVAndToyota();
bool isTruckAndWia();
bool isTruckAndMando();
bool isBoschSteeringForBoschBrake();

std::string getUserSelection();
bool chkUserSelection(std::string userInput, int step);

int getPreviousStep(int step);
void runTest(int answer);
void printSelection(int answer, int step);

enum MenuType {
    MenuCarType,
    MenuEngine,
    MenuBrakeSystem,
    MenuSteeringSystem,
    MenuRunTest,
};

std::string carTypeStr[4] = { "", "Sedan", "SUV", "Truck" };
enum CarType {
    SEDAN = 1,
    SUV,
    TRUCK
};

std::string engineStr[4] = { "", "GM", "TOYOTA", "WIA" };
enum Engine {
    GM = 1,
    TOYOTA,
    WIA
};

std::string brakeSystemStr[4] = { "", "MANDO", "CONTINENTAL", "BOSCH_B" };
enum BrakeSystem {
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};

std::string steeringSystemStr[3] = { "", "BOSCH_S", "MOBIS" };
enum SteeringSystem {
    BOSCH_S = 1,
    MOBIS
};

void makeDelayOnScreen(int ms) {
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

int main() {
    std::string userInput;
    int step = MenuCarType;

    while (true) {
        // �޴� ���
        printMenu(step);

        // ����� ���� ���� �Է�
        userInput = getUserSelection();

        // ���� ��ɾ� �Է� �� �ߴ�.
        if (0 == userInput.compare(EXIT_COMMAND) ) {
            printf(EXIT_MESSAGE);
            break;
        }

        // ����� ���� ������ validation üũ
        if (false == chkUserSelection(userInput, step)) {
            makeDelayOnScreen(DELAY_TIME_FOR_OUTPUT);
            continue;
        }

        int answer = std::stoi(userInput);

        // step �ǵ�����
        if (0 == answer) {
            step = getPreviousStep(step);
        }
        // �׽�Ʈ ����
        else if (MenuRunTest == step) {
            runTest(answer);
        }
        // ��Ÿ(�Ϲ� �޴� ���� ��)
        else {
            printSelection(answer, step);
            makeDelayOnScreen(DELAY_TIME_FOR_OUTPUT);

            step += 1;
        }
    }
}

int getPreviousStep(int step) {
    // ó������ ���ư���
    if (step == MenuRunTest) {
        return MenuCarType;
    }
    // �������� ���ư���
    else {
        return step - 1;
    }
}

void runTest(int answer) {
    // run ���� ��
    if (1 == answer) {
        runProducedCar();
        makeDelayOnScreen(DELAY_TIME_FOR_OUTPUT);
    }
    // test ���� ��
    else if (2 == answer) {
        printf(TEST_LOADING_MESSAGE);
        makeDelayOnScreen(DELAY_FOR_TEST_LOADING);

        testProducedCar();
        makeDelayOnScreen(DELAY_TIME_FOR_OUTPUT);
    }
}


void printSelection(int answer, int step) {
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

void printMenu(int step) {
    printf(CLEAR_SCREEN);

    switch (step) {
    case MenuCarType:
        printMenuCarType();
        break;
    case MenuEngine:
        printMenuEngine();
        break;
    case MenuBrakeSystem:
        printMenuBrakeSystem();
        break;
    case MenuSteeringSystem:
        printMenuSteeringSystem();
        break;
    case MenuRunTest:
        printMenuAction();
        break;
    }
}

void printMenuCarType() {
    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
    printf("� ���� Ÿ���� �����ұ��?\n");
    printf("1. %s\n", carTypeStr[1].c_str());
    printf("2. %s\n", carTypeStr[2].c_str());
    printf("3. %s\n", carTypeStr[3].c_str());
}

void printMenuEngine() {
    printf("� ������ ž���ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. %s\n", engineStr[1].c_str());
    printf("2. %s\n", engineStr[2].c_str());
    printf("3. %s\n", engineStr[3].c_str());
    printf("4. ���峭 ����\n");
}

void printMenuBrakeSystem() {
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. %s\n", brakeSystemStr[1].c_str());
    printf("2. %s\n", brakeSystemStr[2].c_str());
    printf("3. %s\n", brakeSystemStr[3].c_str());
}

void printMenuSteeringSystem() {
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. %s\n", steeringSystemStr[1].c_str());
    printf("2. %s\n", steeringSystemStr[2].c_str());
}

void printMenuAction() {
    printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
    printf("� ������ �ұ��?\n");
    printf("0. ó�� ȭ������ ���ư���\n");
    printf("1. RUN\n");
    printf("2. Test\n");
}

void selectCarType(int answer) {
    userSelection[MenuCarType] = answer;
    printf("���� Ÿ������ %s�� �����ϼ̽��ϴ�.\n", carTypeStr[answer].c_str());
}

void selectEngine(int answer) {
    userSelection[MenuEngine] = answer;
    printf("%s ������ �����ϼ̽��ϴ�.\n", engineStr[answer].c_str());
}

void selectbrakeSystem(int answer) {
    userSelection[MenuBrakeSystem] = answer;
    printf("%s ������ġ�� �����ϼ̽��ϴ�.\n", brakeSystemStr[answer].c_str());
}

void selectSteeringSystem(int answer) {
    userSelection[MenuSteeringSystem] = answer;
    printf("%s ������ġ�� �����ϼ̽��ϴ�.\n", steeringSystemStr[answer].c_str());
}

std::string getUserSelection() {
    printf("===============================\n");

    printf("INPUT > ");
    std::string ret;
    std::cin >> ret;

    // ���� ���๮�� ����
    ret.erase(std::remove(ret.begin(), ret.end(), '\n'), ret.end());

    return ret;
}

bool chkUserSelection(std::string userInput, int step) {
    int answer = 0;

    // ���ڷ� �� ������� Ȯ��
    try {
        answer = std::stoi(userInput);
    } catch (std::invalid_argument e) {
        // �Է¹��� ���ڰ� ���ڰ� �ƴ϶��
        printf("ERROR :: ���ڸ� �Է� ����\n");
        return false;
    }

    // �޴� �Է� ���� Ȯ��
    if (step == MenuCarType && !(answer >= 1 && answer <= 3)) {
        printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
        return false;
    }
    else if (step == MenuEngine && !(answer >= 0 && answer <= 4)) {
        printf("ERROR :: ������ 1 ~ 4 ������ ���� ����\n");
        return false;
    }
    else if (step == MenuBrakeSystem && !(answer >= 0 && answer <= 3)) {
        printf("ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n");
        return false;
    }
    else if (step == MenuSteeringSystem && !(answer >= 0 && answer <= 2)) {
        printf("ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n");
        return false;
    }
    else if (step == MenuRunTest && !(answer >= 0 && answer <= 2)) {
        printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
        return false;
    }

    return true;
}

int isValidCheck() {
    if (true == isSedanAndContinental() || true == isSUVAndToyota() || true == isTruckAndWia() || true == isTruckAndMando() || false == isBoschSteeringForBoschBrake())
        return false;

    return true;
}

void runProducedCar() {
    if (isValidCheck() == false) {
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
    }
    else if (userSelection[MenuEngine] == 4) {
        printf("������ ���峪�ֽ��ϴ�.\n");
        printf("�ڵ����� �������� �ʽ��ϴ�.\n");
    }
    else {
        printf("Car Type : %s\n", carTypeStr[userSelection[MenuCarType]].c_str());
        printf("Engine : %s\n", engineStr[userSelection[MenuEngine]].c_str());
        printf("Brake System : %s\n", brakeSystemStr[userSelection[MenuBrakeSystem]].c_str());
        printf("SteeringSystem : %s\n", steeringSystemStr[userSelection[MenuSteeringSystem]].c_str());

        printf("�ڵ����� ���۵˴ϴ�.\n");
    }
}

void testProducedCar()
{
    if (true == isSedanAndContinental()) {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Sedan���� Continental������ġ ��� �Ұ�\n");
    }
    else if (true == isSUVAndToyota()) {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("SUV���� TOYOTA���� ��� �Ұ�\n");
    }
    else if (true == isTruckAndWia())  {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� WIA���� ��� �Ұ�\n");
    }
    else if (true == isTruckAndMando()) {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� Mando������ġ ��� �Ұ�\n");
    }
    else if (false == isBoschSteeringForBoschBrake()) {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
    }
    else {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
    }
}

bool isBoschSteeringForBoschBrake() {
    if (BOSCH_B != userSelection[MenuBrakeSystem]) {
        return true;
    }
    else if (BOSCH_S != userSelection[MenuSteeringSystem]) {
        return false;
    }

    return true;
}

bool isTruckAndMando() {
    return userSelection[MenuCarType] == TRUCK && userSelection[MenuBrakeSystem] == MANDO;
}

bool isTruckAndWia() {
    return userSelection[MenuCarType] == TRUCK && userSelection[MenuEngine] == WIA;
}

bool isSUVAndToyota() {
    return userSelection[MenuCarType] == SUV && userSelection[MenuEngine] == TOYOTA;
}

bool isSedanAndContinental() {
    return userSelection[MenuCarType] == SEDAN && userSelection[MenuBrakeSystem] == CONTINENTAL;
}

#endif