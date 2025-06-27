#include "gmock/gmock.h"
#include "test_executor.cpp"
#include "combined_car.h"


TEST(RunTestExecutor, ValidCheckSuccess) {
	CombinedCar combinedCar;

	combinedCar.setBrakeSystem(BrakeSystem::MANDO);
	combinedCar.setCarType(CarType::SEDAN);
	combinedCar.setEngine(Engine::GM);
	combinedCar.setSteeringSystem(SteeringSystem::MOBIS);

	bool ret = TestExecutor::getInstance().isValidCheck(combinedCar);

	EXPECT_EQ(true, ret);
}

TEST(RunTestExecutor, ValidCheckSedanAndContinental) {
	CombinedCar combinedCar;

	combinedCar.setBrakeSystem(BrakeSystem::CONTINENTAL);
	combinedCar.setCarType(CarType::SEDAN);
	combinedCar.setEngine(Engine::GM);
	combinedCar.setSteeringSystem(SteeringSystem::MOBIS);

	bool ret = TestExecutor::getInstance().isValidCheck(combinedCar);

	EXPECT_EQ(false, ret);
}

TEST(RunTestExecutor, ValidCheckSUVAndToyota) {
	CombinedCar combinedCar;

	combinedCar.setBrakeSystem(BrakeSystem::CONTINENTAL);
	combinedCar.setCarType(CarType::SUV);
	combinedCar.setEngine(Engine::TOYOTA);
	combinedCar.setSteeringSystem(SteeringSystem::MOBIS);

	bool ret = TestExecutor::getInstance().isValidCheck(combinedCar);

	EXPECT_EQ(false, ret);
}

TEST(RunTestExecutor, ValidCheckTruckAndWia) {
	CombinedCar combinedCar;

	combinedCar.setBrakeSystem(BrakeSystem::CONTINENTAL);
	combinedCar.setCarType(CarType::TRUCK);
	combinedCar.setEngine(Engine::WIA);
	combinedCar.setSteeringSystem(SteeringSystem::MOBIS);

	bool ret = TestExecutor::getInstance().isValidCheck(combinedCar);

	EXPECT_EQ(false, ret);
}

TEST(RunTestExecutor, ValidCheckTruckAndMando) {
	CombinedCar combinedCar;

	combinedCar.setBrakeSystem(BrakeSystem::MANDO);
	combinedCar.setCarType(CarType::TRUCK);
	combinedCar.setEngine(Engine::WIA);
	combinedCar.setSteeringSystem(SteeringSystem::MOBIS);

	bool ret = TestExecutor::getInstance().isValidCheck(combinedCar);

	EXPECT_EQ(false, ret);
}

TEST(RunTestExecutor, ValidCheckBoschSteeringForBoschBrake) {
	CombinedCar combinedCar;

	combinedCar.setBrakeSystem(BrakeSystem::BOSCH_B);
	combinedCar.setCarType(CarType::TRUCK);
	combinedCar.setEngine(Engine::WIA);
	combinedCar.setSteeringSystem(SteeringSystem::MOBIS);

	bool ret = TestExecutor::getInstance().isValidCheck(combinedCar);

	EXPECT_EQ(false, ret);
}

TEST(RunTestExecutor, ErrorStrSuccess) {
	CombinedCar combinedCar;

	combinedCar.setBrakeSystem(BrakeSystem::MANDO);
	combinedCar.setCarType(CarType::SEDAN);
	combinedCar.setEngine(Engine::GM);
	combinedCar.setSteeringSystem(SteeringSystem::MOBIS);

	std::string ret = TestExecutor::getInstance().getInvalidComponent(combinedCar);

	EXPECT_EQ("", ret);
}

TEST(RunTestExecutor, ErrorStrSedanAndContinental) {
	CombinedCar combinedCar;

	combinedCar.setBrakeSystem(BrakeSystem::CONTINENTAL);
	combinedCar.setCarType(CarType::SEDAN);
	combinedCar.setEngine(Engine::GM);
	combinedCar.setSteeringSystem(SteeringSystem::MOBIS);

	std::string ret = TestExecutor::getInstance().getInvalidComponent(combinedCar);

	EXPECT_EQ("Sedan에는 Continental제동장치 사용 불가", ret);
}

TEST(RunTestExecutor, ErrorStrSUVAndToyota) {
	CombinedCar combinedCar;

	combinedCar.setBrakeSystem(BrakeSystem::CONTINENTAL);
	combinedCar.setCarType(CarType::SUV);
	combinedCar.setEngine(Engine::TOYOTA);
	combinedCar.setSteeringSystem(SteeringSystem::MOBIS);

	std::string ret = TestExecutor::getInstance().getInvalidComponent(combinedCar);

	EXPECT_EQ("SUV에는 TOYOTA엔진 사용 불가", ret);
}

TEST(RunTestExecutor, ErrorStrTruckAndWia) {
	CombinedCar combinedCar;

	combinedCar.setBrakeSystem(BrakeSystem::CONTINENTAL);
	combinedCar.setCarType(CarType::TRUCK);
	combinedCar.setEngine(Engine::WIA);
	combinedCar.setSteeringSystem(SteeringSystem::MOBIS);

	std::string ret = TestExecutor::getInstance().getInvalidComponent(combinedCar);

	EXPECT_EQ("Truck에는 WIA엔진 사용 불가", ret);
}

TEST(RunTestExecutor, ErrorStrTruckAndMando) {
	CombinedCar combinedCar;

	combinedCar.setBrakeSystem(BrakeSystem::MANDO);
	combinedCar.setCarType(CarType::TRUCK);
	combinedCar.setEngine(Engine::GM);
	combinedCar.setSteeringSystem(SteeringSystem::MOBIS);

	std::string ret = TestExecutor::getInstance().getInvalidComponent(combinedCar);

	EXPECT_EQ("Truck에는 Mando제동장치 사용 불가", ret);
}

TEST(RunTestExecutor, ErrorStrBoschSteeringForBoschBrake) {
	CombinedCar combinedCar;

	combinedCar.setBrakeSystem(BrakeSystem::BOSCH_B);
	combinedCar.setCarType(CarType::TRUCK);
	combinedCar.setEngine(Engine::GM);
	combinedCar.setSteeringSystem(SteeringSystem::MOBIS);

	std::string ret = TestExecutor::getInstance().getInvalidComponent(combinedCar);

	EXPECT_EQ("Bosch제동장치에는 Bosch조향장치 이외 사용 불가", ret);
}

TEST(Components, ComponentNameMatch) {
	CombinedCar combinedCar;

	combinedCar.setBrakeSystem(BrakeSystem::BOSCH_B);
	combinedCar.setCarType(CarType::TRUCK);
	combinedCar.setEngine(Engine::GM);
	combinedCar.setSteeringSystem(SteeringSystem::MOBIS);

	EXPECT_EQ("BOSCH_B", combinedCar.getBrakeSystemName());
	EXPECT_EQ("Truck", combinedCar.getCarTypeName());
	EXPECT_EQ("GM", combinedCar.getEngineName());
	EXPECT_EQ("MOBIS", combinedCar.getSteeringSystemName());
}

TEST(Components, ComponentKindMatch) {
	const std::vector<std::string> carTypes = CarType::getInstance().getCarTypes();
	const std::vector<std::string> Engines = Engine::getInstance().getEngines();
	const std::vector<std::string> brakeSystems = BrakeSystem::getInstance().getBrakeSystems();
	const std::vector<std::string> steeringSystems = SteeringSystem::getInstance().getSteeringSystem();

	int carTypeKind = CarType::getInstance().getCarTypeKind();
	int engineKind = Engine::getInstance().getEngineKind();
	int brakeSystemKind = BrakeSystem::getInstance().getBrakeSystemKind();
	int steeringSystemKind = SteeringSystem::getInstance().getSteeringSystemKind();
	
	EXPECT_EQ(carTypeKind, carTypes.size());
	EXPECT_EQ(engineKind, Engines.size());
	EXPECT_EQ(brakeSystemKind, brakeSystems.size());
	EXPECT_EQ(steeringSystemKind, steeringSystems.size());
}