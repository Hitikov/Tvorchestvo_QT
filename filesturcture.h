#ifndef FILESTURCTURE_H
#define FILESTURCTURE_H

#include<QString>

class FileSturcture
{
public:
    FileSturcture();
    void CreateFile();
    void DeleteFile();
    void ReadFile();
    void EditFile();
protected:
    QString filename;
    QString path;
};

class TestProject:public FileSturcture
{
public:
    TestProject();
protected:
    int questionCount;
    int baseScore;
    QString creator;
};

class TestRecord:public FileSturcture
{
public:
    TestRecord();
protected:
    int resultScore;
    int baseScore;
    QString resultCompletitionDate;
    QString testname;
    QString solver;
};


#endif // FILESTURCTURE_H
