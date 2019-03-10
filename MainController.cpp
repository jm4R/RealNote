#include "MainController.hpp"

#include "Commands.hpp"
#include "Model/ApplicationContext.hpp"
#include "Model/Global.hpp"
#include "Model/NoteModel.hpp"
#include "Themes.hpp"

#include <QApplication>
#include <QDebug>
#include <QLocalServer>
#include <QLocalSocket>

MainController::MainController(QObject* parent) : QObject{parent}
{
    qApp->setStyleSheet(Themes::style());

    window_.show();
    window_.setNotesTreeModel(context->notes);

    {
        QLocalSocket socket;
        socket.connectToServer(Global::appUuid());
        socket.waitForConnected();
        if (socket.isOpen())
        {
            socket.close();
            throw 1;
        }
    }

    auto server = new QLocalServer(this);
    server->setSocketOptions(QLocalServer::WorldAccessOption);
    server->listen(Global::appUuid());
    QObject::connect(server, &QLocalServer::newConnection, [&] {
        // Solution not portable:
        // https://stackoverflow.com/questions/6087887/bring-window-to-front-raise-show-activatewindow-don-t-work
        window_.activateWindow();
        window_.raise();
        window_.setWindowState((window_.windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
    });

    connect(&window_, &MainWindow::saveInvoked, this, &MainController::save);
    connect(&window_, &MainWindow::noteChoosed, [](const QModelIndex& index) { cmd::setNote(index); });
    connect(&window_, &MainWindow::addNote,
            [](const QModelIndex& position, const QString& name) { cmd::addNote(position, name); });
    connect(&window_, &MainWindow::removeNote, [](const QModelIndex& index) { cmd::removeNote(index); });
    connect(&window_, &MainWindow::addCategory,
            [](const QModelIndex& position, const QString& name) { cmd::addCategory(position, name); });
    connect(&window_, &MainWindow::removeCategory, [](const QModelIndex& index) { cmd::removeCategory(index); });
}

void MainController::save() // TODO: make command
{
    if (!context->note)
        return;
    context->note->save();
}
