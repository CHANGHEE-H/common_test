#include <iostream>

#include "test_executor.cpp"
#include "screen_printer.cpp"

#define DELAY_TIME_FOR_OUTPUT 2000
#define DELAY_FOR_TEST_LOADING 1500

#define EXIT_COMMAND "exit"

class UserInterface {
public:
	void run() {
		std::string userInput;
		int step = MenuCarType;

		while (true) {
			// 메뉴 출력
            ScreenPrinter::printMenu(step);

			// 사용자 선택 정보 입력
			userInput = getUserSelection();

			// 종료 명령어 입력 시 중단.
			if (0 == userInput.compare(EXIT_COMMAND)) {
                ScreenPrinter::printExitMessage();
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
                answer -= 1;
                if (step == MenuCarType) {
                    m_combinedCar.setCarType(answer);
                }
                else if (step == MenuEngine) {
                    m_combinedCar.setEngine(answer);
                }
                else if (step == MenuBrakeSystem) {
                    m_combinedCar.setBrakeSystem(answer);
                }
                else if (step == MenuSteeringSystem) {
                    m_combinedCar.setSteeringSystem(answer);
                }

                ScreenPrinter::printSelection(answer, step);
				makeDelayOnScreen(DELAY_TIME_FOR_OUTPUT);

				step += 1;
			}
		}
	}
private:
    CombinedCar m_combinedCar;

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
            ScreenPrinter::printTestLoading();
            makeDelayOnScreen(DELAY_FOR_TEST_LOADING);

            testProducedCar();
            makeDelayOnScreen(DELAY_TIME_FOR_OUTPUT);
        }
    }

    std::string getUserSelection() {
        ScreenPrinter::printInputLoading();

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
        }
        catch (std::invalid_argument e) {
            // 입력받은 문자가 숫자가 아니라면
            ScreenPrinter::printSelectionFormatError();
            return false;
        }

        // 메뉴 입력 범위 확인
        if (
            (step == MenuCarType && !(answer >= 1 && answer <= CarType::getInstance().getCarTypeKind())) ||
            (step == MenuEngine && !(answer >= 0 && answer <= Engine::getInstance().getEngineKind())) ||
            (step == MenuBrakeSystem && !(answer >= 0 && answer <= BrakeSystem::getInstance().getBrakeSystemKind())) ||
            (step == MenuSteeringSystem && !(answer >= 0 && answer <= SteeringSystem::getInstance().getSteeringSystemKind())) ||
            (step == MenuRunTest && !(answer >= 0 && answer <= 2))
        ) {
            ScreenPrinter::printSelectionRangeError(step);
            return false;
        }

        return true;
    }

	void runProducedCar() {
		if (false == TestExecutor::getInstance().isValidCheck(m_combinedCar)) {
            ScreenPrinter::printUnavailableCar();
		}
		else if (Engine::WRONG_ENGINE == m_combinedCar.getEngine()) {
            ScreenPrinter::printUnavailableEngine();
		}
		else {
            ScreenPrinter::printAvailableCar(m_combinedCar);
		}
	}

	void testProducedCar() {
		if (true == TestExecutor::getInstance().isValidCheck(m_combinedCar)) {
            ScreenPrinter::printTestPass();
		}
		else {
            ScreenPrinter::printTestFail(TestExecutor::getInstance().getInvalidComponent(m_combinedCar).c_str());
		}
	}
};