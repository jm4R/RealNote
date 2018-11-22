#include "NoteModel.h"

#include "Model/Global.h"

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFontDatabase>
#include <QPlainTextDocumentLayout>
#include <QStandardPaths>
#include <QTextStream>

namespace {

void cdOrCreate(QDir& dir, const QString& dirName)
{
    if (!dir.cd(dirName))
    {
        if (!dir.mkdir(dirName))
        {
            // TODO
        }
        dir.cd(dirName);
    }
}

} // namespace

const QString NoteModel::DATA_LOCATION =
    QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

NoteModel::NoteModel(const QString& fileName)
    : _state{NOT_LOADED}
    , _fileName(fileName)
{
    auto l = new QPlainTextDocumentLayout{&_document}; // TODO
    _document.setDocumentLayout(l);
    auto font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    font.setPointSize(11);
    _document.setDefaultFont(font);
}

void NoteModel::load()
{
    /* load file */ {
        const auto fullPath = getCurrentVersionPath();
        qDebug() << "Loading file: " << fullPath;
        QFile data{fullPath};
        if (data.open(QFile::ReadOnly))
        {
            QTextStream stream{&data};
            _document.setPlainText(stream.readAll());
            _state = LOADED;
            _document.setModified(false);
        }
        else
        {
            // TODO
        }
    }

    /* load history */ {
        _versions = getHistoricalVersionsPath().entryList(QDir::Files, QDir::Name | QDir::Reversed);
    }
}

void NoteModel::save()
{
    if (!_document.isModified())
        return;

    archiveCurrentVersion();
    const auto fullPath = getCurrentVersionPath();
    save(fullPath, _document.toRawText());
    preventHistoricalVersionsOverload();
    _state = LOADED;

    _document.setModified(false);
}

QTextDocument& NoteModel::document()
{
    if (_state == NOT_LOADED)
        load();
    return _document;
}

const QStringList& NoteModel::versions() const
{
    return _versions;
}

QString NoteModel::humanReadableVersion(QString version)
{
    return QDateTime::fromMSecsSinceEpoch(version.toLongLong()).toString(Qt::SystemLocaleShortDate);
}

QString NoteModel::getCurrentVersionPath() const
{
    QDir dir{DATA_LOCATION};
    cdOrCreate(dir, Global::appName());
    return dir.filePath(_fileName);
}

QDir NoteModel::getHistoricalVersionsPath() const
{
    QDir dir{DATA_LOCATION};
    cdOrCreate(dir, Global::appName());
    cdOrCreate(dir, Global::historyDirName());
    cdOrCreate(dir, _fileName);
    return dir;
}

void NoteModel::save(const QString& fileName, const QString& text)
{
    qDebug() << "Saving file: " << fileName;
    QFile data{fileName};
    if (data.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream stream{&data};
        stream << text;
    }
    else
    {
        // TODO
    }
}

void NoteModel::archiveCurrentVersion()
{
    const auto oldFilePath = getCurrentVersionPath();
    QDir dir = getHistoricalVersionsPath();
    QString timestamp = QString::number(QDateTime::currentMSecsSinceEpoch());
    const auto newFilePath = dir.filePath(timestamp);

    qDebug() << "Archiving " << oldFilePath << " to " << newFilePath;
    if (!QFile::rename(oldFilePath, newFilePath))
    {
        // TODO
        return;
    }

    _versions.prepend(timestamp);
}

void NoteModel::preventHistoricalVersionsOverload()
{
    const auto toDelete = _versions.size() - Global::historyCapacity();
    QDir dir = getHistoricalVersionsPath();
    for (auto i = 0; i < toDelete; ++i)
    {
        const auto fileName = _versions.back();
        dir.remove(fileName);
        _versions.removeLast();
    }
}

void NoteModel::unload()
{
    _state = (_state == NOT_ON_DISC) ? NOT_ON_DISC : NOT_LOADED;
    _document.clear();
}
