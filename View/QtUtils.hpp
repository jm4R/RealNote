#ifndef QTUTILS_HPP
#define QTUTILS_HPP

#include "TextEditor.hpp"

#include <QAction>
#include <QInputDialog>
#include <QLayout>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QSplitter>
#include <QToolButton>
#include <QTreeView>
#include <QWidget>

#include <type_traits>

namespace detail
{
template<typename L, typename... T>
void fillLayout(L* layout, T*... items)
{
    auto add = [&](auto* item) {
        if constexpr (std::is_base_of_v<QWidget, std::decay_t<decltype(*item)>>)
            layout->addWidget(item);
        else if (std::is_base_of_v<QLayout, std::decay_t<decltype(*item)>>)
            layout->addLayout(item);
    };
    (add(items), ...);
}
} // namespace detail

namespace QtUtils
{

template<typename... T>
QHBoxLayout* hLayout(QWidget* parent, T*... items)
{
    auto layout = new QHBoxLayout{parent};
    detail::fillLayout(layout, items...);
    return layout;
}

template<typename... T>
QVBoxLayout* vLayout(QWidget* parent, T*... items)
{
    auto layout = new QVBoxLayout{parent};
    detail::fillLayout(layout, items...);
    return layout;
}

template<typename... T>
QSplitter* splitter(QWidget* parent, T*... widgets)
{
    auto splitter = new QSplitter{parent};
    (splitter->addWidget(widgets), ...);
    return splitter;
}

template<typename F>
QAction* action(QWidget* parent, const QString& label, F&& handler)
{
    auto action = new QAction{label, parent};
    QObject::connect(action, &QAction::triggered, handler);
    return action;
}

bool confirmDialog(QWidget* parent, const QString& question)
{
    return QMessageBox::Yes == QMessageBox::question(parent, QObject::tr("Please confirm"), question);
}

} // namespace QtUtils

#endif // QTUTILS_HPP
