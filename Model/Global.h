#ifndef APPLICATION_H
#define APPLICATION_H

namespace Global
{
    inline const char* appName()
    {
        return "RealNote";
    }

    inline const char* appUuid()
    {
        return "thisRealNoteApplicationIsSuchUnique";
    }

    inline const char* historyDirName()
    {
        return ".history";
    }

    inline int historyCapacity()
    {
        return 10;
    }
}

#endif // APPLICATION_H
