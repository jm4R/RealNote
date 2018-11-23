#include "Model/ApplicationContext.hpp"

Application::Application(int argc, char** argv) : QApplication{argc, argv}
{
    context = std::unique_ptr<ApplicationContext>{new ApplicationContext{}};
    ::context = context.get();
}
