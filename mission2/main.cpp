#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include "user_interface.cpp"

int main() {
    UserInterface userInterface;

    userInterface.run();
}

#endif