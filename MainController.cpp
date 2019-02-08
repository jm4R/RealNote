#include "MainController.hpp"

#include "Model/Global.hpp"

#include <QApplication>
#include <QDebug>
#include <QLocalServer>
#include <QLocalSocket>

MainController::MainController(QObject* parent) : QObject{parent}, note_{nullptr}
{
    // QFile file("qrc:/dark.css");
    // const auto qss = QString::fromUtf8(file.readAll());
    // qDebug() << qss;
    // qApp->setStyleSheet("QWidget { background-color: #404244; color: #BBBBBB} QPlainTextEdit { background-color:
    // #000000; color: #EEEEEE } QTreeWidget { background-color: #2E2F30 } LineNumberWidget { background-color: #232323
    // }");

    window_.show();
    window_.setNotesTreeModel(notes_);

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
    connect(&window_, &MainWindow::noteChoosed, [&](const QModelIndex& index) {
        NoteModel* note = notes_.noteAt(index); // TODO: move from here
        if (note)
        {
            window_.setNote(*note);
            note_ = note;
        }
    });
}

void MainController::save()
{
    if (!note_)
        return;
    note_->save();
    window_.updateNote();
}
