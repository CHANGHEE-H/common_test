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
#define EXIT_MESSAGE "바이바이\n"

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
        // 메뉴 출력
        printMenu(step);

        // 사용자 선택 정보 입력
        userInput = getUserSelection();

        // 종료 명령어 입력 시 중단.
        if (0 == userInput.compare(EXIT_COMMAND) ) {
            printf(EXIT_MESSAGE);
            break;
        }

        // 사용자 선택 정보의 validation 체크
        if (false == chkUserSelection(userInput, step)) {
            makeDelayOnScreen(DELAY_TIME_FOR_OUTPUT);
            continue;
        }

        int answer = std::stoi(userInput);

        // step 되돌리기
        if (0 == answer) {
            step = getPreviousStep(step);
        }
        // 테스트 실행
        else if (MenuRunTest == step) {
            runTest(answer);
        }
        // 기타(일반 메뉴 선택 시)
        else {
            printSelection(answer, step);
            makeDelayOnScreen(DELAY_TIME_FOR_OUTPUT);

            step += 1;
        }
    }
}

int getPreviousStep(int step) {
    // 처음으로 돌아가기
    if (step == MenuRunTest) {
        return MenuCarType;
    }
    // 이전으로 돌아가기
    else {
        return step - 1;
    }
}

void runTest(int answer) {
    // run 실행 시
    if (1 == answer) {
        runProducedCar();
        makeDelayOnScreen(DELAY_TIME_FOR_OUTPUT);
    }
    // test 실행 시
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
    printf("어떤 차량 타입을 선택할까요?\n");
    printf("1. %s\n", carTypeStr[1].c_str());
    printf("2. %s\n", carTypeStr[2].c_str());
    printf("3. %s\n", carTypeStr[3].c_str());
}

void printMenuEngine() {
    printf("어떤 엔진을 탑재할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. %s\n", engineStr[1].c_str());
    printf("2. %s\n", engineStr[2].c_str());
    printf("3. %s\n", engineStr[3].c_str());
    printf("4. 고장난 엔진\n");
}

void printMenuBrakeSystem() {
    printf("어떤 제동장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. %s\n", brakeSystemStr[1].c_str());
    printf("2. %s\n", brakeSystemStr[2].c_str());
    printf("3. %s\n", brakeSystemStr[3].c_str());
}

void printMenuSteeringSystem() {
    printf("어떤 조향장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. %s\n", steeringSystemStr[1].c_str());
    printf("2. %s\n", steeringSystemStr[2].c_str());
}

void printMenuAction() {
    printf("멋진 차량이 완성되었습니다.\n");
    printf("어떤 동작을 할까요?\n");
    printf("0. 처음 화면으로 돌아가기\n");
    printf("1. RUN\n");
    printf("2. Test\n");
}

void selectCarType(int answer) {
    userSelection[MenuCarType] = answer;
    printf("차량 타입으로 %s을 선택하셨습니다.\n", carTypeStr[answer].c_str());
}

void selectEngine(int answer) {
    userSelection[MenuEngine] = answer;
    printf("%s 엔진을 선택하셨습니다.\n", engineStr[answer].c_str());
}

void selectbrakeSystem(int answer) {
    userSelection[MenuBrakeSystem] = answer;
    printf("%s 제동장치를 선택하셨습니다.\n", brakeSystemStr[answer].c_str());
}

void selectSteeringSystem(int answer) {
    userSelection[MenuSteeringSystem] = answer;
    printf("%s 조향장치를 선택하셨습니다.\n", steeringSystemStr[answer].c_str());
}

std::string getUserSelection() {
    printf("===============================\n");

    printf("INPUT > ");
    std::string ret;
    std::cin >> ret;

    // 엔터 개행문자 제거
    ret.erase(std::remove(ret.begin(), ret.end(), '\n'), ret.end());

    return ret;
}

bool chkUserSelection(std::string userInput, int step) {
    int answer = 0;

    // 숫자로 된 대답인지 확인
    try {
        answer = std::stoi(userInput);
    } catch (std::invalid_argument e) {
        // 입력받은 문자가 숫자가 아니라면
        printf("ERROR :: 숫자만 입력 가능\n");
        return false;
    }

    // 메뉴 입력 범위 확인
    if (step == MenuCarType && !(answer >= 1 && answer <= 3)) {
        printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
        return false;
    }
    else if (step == MenuEngine && !(answer >= 0 && answer <= 4)) {
        printf("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n");
        return false;
    }
    else if (step == MenuBrakeSystem && !(answer >= 0 && answer <= 3)) {
        printf("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n");
        return false;
    }
    else if (step == MenuSteeringSystem && !(answer >= 0 && answer <= 2)) {
        printf("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n");
        return false;
    }
    else if (step == MenuRunTest && !(answer >= 0 && answer <= 2)) {
        printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
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
        printf("자동차가 동작되지 않습니다\n");
    }
    else if (userSelection[MenuEngine] == 4) {
        printf("엔진이 고장나있습니다.\n");
        printf("자동차가 움직이지 않습니다.\n");
    }
    else {
        printf("Car Type : %s\n", carTypeStr[userSelection[MenuCarType]].c_str());
        printf("Engine : %s\n", engineStr[userSelection[MenuEngine]].c_str());
        printf("Brake System : %s\n", brakeSystemStr[userSelection[MenuBrakeSystem]].c_str());
        printf("SteeringSystem : %s\n", steeringSystemStr[userSelection[MenuSteeringSystem]].c_str());

        printf("자동차가 동작됩니다.\n");
    }
}

void testProducedCar()
{
    if (true == isSedanAndContinental()) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
    }
    else if (true == isSUVAndToyota()) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
    }
    else if (true == isTruckAndWia())  {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
    }
    else if (true == isTruckAndMando()) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
    }
    else if (false == isBoschSteeringForBoschBrake()) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
    }
    else {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
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