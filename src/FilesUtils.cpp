#include "FilesUtils.hpp"

#include "Model/Global.hpp"

#include <QDir>
#include <QStandardPaths>

namespace Dir
{

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

QString dataLocation()
{
    static QString location = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    return location;
}

QDir dataDir()
{
    QDir dir{Dir::dataLocation()};
    if (!dir.exists())
    {
        if (!dir.mkpath("."))
        {
            // TODO
        }
    }
    Dir::cdOrCreate(dir, Global::notesDirName());
    return dir;
}

QStringList listDirs(const QDir& dir)
{
    auto config = QDir::Dirs | QDir::NoDotAndDotDot | QDir::Readable;
    return dir.entryList(config);
}

QStringList listFiles(const QDir& dir)
{
    auto config = QDir::Files | QDir::NoSymLinks | QDir::Readable;
    return dir.entryList(config);
}
} // namespace Dir
