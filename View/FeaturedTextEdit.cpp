#include "FeaturedTextEdit.h"

#include <QtWidgets>

namespace {
    constexpr auto ADDITIONAL_SPACE = 16;
}

class FeaturedTextEdit::LineNumberWidget : public QWidget
{
public:
    LineNumberWidget(FeaturedTextEdit* editor)
        : QWidget(editor)
    {
        codeEditor = editor;
    }

    QSize sizeHint() const override
    {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent* event) override
    {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    FeaturedTextEdit* codeEditor;
};

FeaturedTextEdit::FeaturedTextEdit(QWidget* parent)
    : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberWidget(this);

    connect(document(), &QTextDocument::contentsChange, this,
            &FeaturedTextEdit::updateLineNumberAreaWidth);
    connect(this, &QPlainTextEdit::updateRequest, this, &FeaturedTextEdit::updateLineNumberArea);

    updateLineNumberAreaWidth();
}

int FeaturedTextEdit::lineNumberAreaWidth()
{
    return fontMetrics().width(QString::number(document()->lineCount())) + ADDITIONAL_SPACE;
}

void FeaturedTextEdit::updateLineNumberAreaWidth()
{
    setFont(document()->defaultFont());
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void FeaturedTextEdit::updateLineNumberArea(const QRect& rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth();
}

void FeaturedTextEdit::resizeEvent(QResizeEvent* e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void FeaturedTextEdit::lineNumberAreaPaintEvent(QPaintEvent* event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), QColor(35, 35, 35));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = int(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + int(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            //painter.setPen(Qt::green);
            painter.drawText(0, top, lineNumberArea->width() - ADDITIONAL_SPACE/2, fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + int(blockBoundingRect(block).height());
        ++blockNumber;
    }
}
