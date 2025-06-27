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
			// �޴� ���
            ScreenPrinter::printMenu(step);

			// ����� ���� ���� �Է�
			userInput = getUserSelection();

			// ���� ��ɾ� �Է� �� �ߴ�.
			if (0 == userInput.compare(EXIT_COMMAND)) {
                ScreenPrinter::printExitMessage();
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

        // ���� ���๮�� ����
        ret.erase(std::remove(ret.begin(), ret.end(), '\n'), ret.end());

        return ret;
    }

    bool chkUserSelection(std::string userInput, int step) {
        int answer = 0;

        // ���ڷ� �� ������� Ȯ��
        try {
            answer = std::stoi(userInput);
        }
        catch (std::invalid_argument e) {
            // �Է¹��� ���ڰ� ���ڰ� �ƴ϶��
            ScreenPrinter::printSelectionFormatError();
            return false;
        }

        // �޴� �Է� ���� Ȯ��
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