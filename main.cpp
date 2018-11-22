#include "MainController.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    try
    {
        MainController mc;
        mc.moveToThread(a.thread());
        return a.exec();
    }
    catch (int&)
    {
        //other instance runs
    }
    return 0;
}
