#include "MainController.hpp"
#include "Model/ApplicationContext.hpp"

int main(int argc, char* argv[])
{
    Application a(argc, argv);

    try
    {
        MainController mc;
        mc.moveToThread(a.thread());
        return a.exec();
    }
    catch (int&)
    {
        // other instance runs
    }
    return 0;
}
