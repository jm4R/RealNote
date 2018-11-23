#ifndef FILESUTILS_HPP
#define FILESUTILS_HPP

class QDir;
class QString;
class QStringList;

namespace Dir {

void cdOrCreate(QDir& dir, const QString& dirName);
QString dataLocation();
QDir dataDir();
QStringList listDirs(const QDir& dir);
QStringList listFiles(const QDir& dir);

}



#endif // FILESUTILS_HPP
