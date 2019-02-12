#ifndef APPLICATIONCONTEXT_HPP
#define APPLICATIONCONTEXT_HPP

#include "Model/NotesContainer.hpp"

#include <QApplication>
#include <memory>

class ApplicationContext;

class Application : public QApplication
{
public:
    explicit Application(int argc, char** argv);
    std::unique_ptr<ApplicationContext> context;
};

class NoteModel;

class ApplicationContext
{
    ApplicationContext() = default;
public:
    friend class Application;
    ApplicationContext(const ApplicationContext&) = delete;
    ApplicationContext operator=(const ApplicationContext&) = delete;

    // application model:
    NotesContainer notes;
    NoteModel* note;
};

inline ApplicationContext* context;

#endif // APPLICATIONCONTEXT_HPP
