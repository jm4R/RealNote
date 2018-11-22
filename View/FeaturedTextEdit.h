#ifndef FEATURED_TEXT_EDIT
#define FEATURED_TEXT_EDIT

#include <QPlainTextEdit>
#include <QObject>

class QPaintEvent;
class QResizeEvent;
class QWidget;


class FeaturedTextEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    FeaturedTextEdit(QWidget *parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth();
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
    class LineNumberWidget;
};


#endif
