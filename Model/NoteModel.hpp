#ifndef NOTEMODEL_H
#define NOTEMODEL_H

#include <QDir>
#include <QString>
#include <QStringList>
#include <QTextDocument>

class NoteModel
{
public:
    NoteModel(const QString& categoryName, const QString& fileName);
    NoteModel(NoteModel&& other) = default;

    void load();
    void save();
    void unload();
    QTextDocument& document();
    const QStringList& versions() const;
    QString name() const;

    static QString humanReadableVersion(QString version);

private:
    QString getCurrentVersionPath() const;
    QDir getHistoricalVersionsPath() const;
    static void save(const QString& fileName, const QString& text);
    void archiveCurrentVersion();
    void preventHistoricalVersionsOverload();

private:
    enum State
    {
        NOT_ON_DISC,
        LOADED,
        NOT_LOADED
    } _state;

    QString _categoryName;
    QString _fileName;
    QStringList _versions;
    // QStringList::Iterator _loadedVersion;
    QTextDocument _document;
};

#endif // NOTEMODEL_H
