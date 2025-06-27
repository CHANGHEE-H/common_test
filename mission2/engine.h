#pragma once
#include <string>
#include <vector>

class Engine {
public:
    enum Engine_E {
        GM,
        TOYOTA,
        WIA,
        WRONG_ENGINE
    };

    static Engine& getInstance();
    const std::vector<std::string> getEngines();
    std::string getEngineName(int engine);
    int getEngineKind();

private:
    Engine() {}
    ~Engine() {}

    std::vector<std::string> m_engineStr = { "GM", "TOYOTA", "WIA", "고장난 엔진"};
};