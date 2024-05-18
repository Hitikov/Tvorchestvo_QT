#include "filesystemactions.h"

#include <QTextStream>
#include <QUrl>
#include <QProcess>

//Просмотр содержимого директории
QFileInfoList ViewDirectory(int mode)
{
    QDir viewDir; //Название дирректории для открытия
    QStringList nameFilter; //Фильтр поиска

    //Выбор соответствующей директории исходя из значения параметра mode
    if (mode == WorkMode::TEST_PROJECTS)
    {
        viewDir.setPath("TestProjects");
        nameFilter << "*.usertestfile";
    }
    else if (mode == WorkMode::RESULT_RECORDS)
    {
        viewDir.setPath("ResultRecords");
        nameFilter << "*.userresultrecord";
    }

    //Получение информации о хранящихся в директории файлах
    QFileInfoList fileList = viewDir.entryInfoList(nameFilter, QDir::Files);

    return fileList;
}

//Создание файла, название, директория хранения и содержимое файла определяются входными параметрами
void CreateFile(int mode, QString namebase, QStringList inInfo)
{
    QString fileExtention; //Расширение файла
    QString filename; //Название файла
    QString absPath; //Абсолютный путь до директории

    //Выбор соответствующей директории исходя из значения параметра mode
    if (mode == WorkMode::TEST_PROJECTS)
    {
        absPath = QDir::currentPath() + "/TestProjects/";
        fileExtention = ".usertestfile";
        filename =  absPath + namebase + fileExtention;
    }
    else if (mode == WorkMode::RESULT_RECORDS)
    {
        absPath = QDir::currentPath() + "/ResultRecords/";
        fileExtention = ".userresultrecord";
        filename = absPath + namebase + fileExtention;
    }

    //Попытка открытия файлового потока, при неудаче завершение функции
    QFile outFile(filename);
    if(!outFile.open(QIODevice::WriteOnly)) {
        return;
    }

    //Запись содержимого параметра inInfo в файл
    QTextStream out(&outFile);

    auto iter = inInfo.begin();

    while (!(iter == inInfo.end())){
        out << *iter << endl;
        iter += 1;
    }

    outFile.close();
}

//Чтение файла, название, директория хранения определяются входными параметрами
QStringList ReadFile(int mode, QString namebase)
{
    QString fileExtention; //Расширение файла
    QString filename; //Название файла
    QString absPath; //Абсолютный путь до директории

    //Выбор соответствующей директории исходя из значения параметра mode
    if (mode == WorkMode::TEST_PROJECTS)
    {
        absPath = QDir::currentPath() + "/TestProjects/";
        fileExtention = ".usertestfile";
        filename =  absPath + namebase + fileExtention;
    }
    else if (mode == WorkMode::RESULT_RECORDS)
    {
        absPath = QDir::currentPath() + "/ResultRecords/";
        fileExtention = ".userresultrecord";
        filename = absPath + namebase + fileExtention;
    }

    QStringList fileContent{};

    //Попытка открытия файлового потока, при неудаче завершение функции
    QFile inFile(filename);
    if(!inFile.open(QIODevice::ReadOnly)) {
        return fileContent;
    }

    //Запись содержимого файла в переменную fileContent
    QTextStream in(&inFile);

    while (!in.atEnd())
    {
        fileContent.append(in.readLine());
    }
    inFile.close();

    return fileContent;
}

//Проверка существования директории, создание директорий при отсутствии
void PrepairFileSpace()
{
   const QString dir = "TestProjects";
    if(!QDir(dir).exists())
        QDir().mkdir(dir);

    if(!QDir("ResultRecords").exists())
       QDir().mkdir("ResultRecords");
}

//Открытие директории через проводник, директория определяется
void OpenDirectory(int mode)
{
    QString absPath;

    //Определение директории
    if (mode == WorkMode::TEST_PROJECTS)
    {
        absPath = QDir::currentPath() + "\\TestProjects\\";
    }
    else if (mode == WorkMode::RESULT_RECORDS)
    {
        absPath =  QDir::currentPath() + "\\ResultRecords\\";
    }

    absPath.replace("/", "\\");

    //Открытие директории в стандартном проводнике
    //absPath = "/select," + absPath;
    QProcess::startDetached("explorer.exe", {absPath});

}

//Старые функции
//Чтение файла, название, директория хранения определяются входными параметрами
/*
void EditFile(int mode, QString namebase)
{
    QString fileExtention;
    QString filename;
    QString absPath;
    if (mode == WorkMode::TEST_PROJECTS)
    {
        absPath = QDir::currentPath() + "/TestProjects/";
        fileExtention = ".usertestfile";
        filename =  absPath + namebase + fileExtention;
    }
    else if (mode == WorkMode::RESULT_RECORDS)
    {
        absPath = QDir::currentPath() + "/ResultRecords/";
        fileExtention = ".userresultrecord";
        filename = absPath + namebase + fileExtention;
    }

    filename.replace("/", "\\");

    QProcess::startDetached("explorer.exe", {filename});
}
*/
