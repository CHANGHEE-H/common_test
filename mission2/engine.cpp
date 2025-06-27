#include "engine.h"

Engine& Engine::getInstance() {
    static Engine instance;
    return instance;
}

const std::vector<std::string> Engine::getEngines() {
    return m_engineStr;
}

std::string Engine::getEngineName(int engine) {
    return m_engineStr[engine];
}

int Engine::getEngineKind() {
    return (int)m_engineStr.size();
}