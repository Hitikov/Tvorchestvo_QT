#ifndef FILESYSTEMACTIONS_H
#define FILESYSTEMACTIONS_H

#include <QDir>
#include "WorkMode.h"

QFileInfoList ViewDirectory(int mode);

void CreateFile(int mode, QString namebase, QStringList inInfo);

QStringList ReadFile(int mode, QString namebase);

//void DeleteFile(int mode, QString namebase); Will be added later

//void EditFile(int mode, QString namebase); Unused function

void PrepairFileSpace();

void OpenDirectory(int mode);

#endif // FILESYSTEMACTIONS_H
