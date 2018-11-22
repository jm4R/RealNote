#include "MainController.h"

#include "Model/Global.h"

#include <QApplication>
#include <QDebug>
#include <QLocalServer>
#include <QLocalSocket>

MainController::MainController(QObject* parent)
    : QObject(parent)
    , note_{"DefaultNote"}
{
    QFile file("qrc:/dark.css");
    const auto qss = QString::fromUtf8(file.readAll());
    qDebug() << qss;
    qApp->setStyleSheet("QWidget { background-color: #404244; color: #BBBBBB} QPlainTextEdit { background-color: #000000; color: #EEEEEE } QTreeWidget { background-color: #2E2F30 } LineNumberWidget { background-color: #232323 }");

    connect(&window_, &MainWindow::saveInvoked, this, &MainController::save);
    window_.show();
    window_.setNote(note_);

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
        // Solution not portable: https://stackoverflow.com/questions/6087887/bring-window-to-front-raise-show-activatewindow-don-t-work
        window_.activateWindow();
        window_.raise();
        window_.setWindowState( (window_.windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
    });
}

void MainController::save()
{
    note_.save();
    window_.updateNote();
}
