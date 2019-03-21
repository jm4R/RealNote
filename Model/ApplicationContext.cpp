#include "Model/ApplicationContext.hpp"

#include "Model/Global.hpp"

Application::Application(int argc, char** argv) : QApplication{argc, argv}
{
    context = std::unique_ptr<ApplicationContext>{new ApplicationContext{}};
    ::context = context.get();
}

ApplicationContext::ApplicationContext()
    : settings{QSettings::IniFormat, QSettings::UserScope, Global::appName()}
{

}
