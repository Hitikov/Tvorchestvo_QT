#include "corewindow.h"
#include "ui_corewindow.h"
#include "testcreatorwindow.h"
#include "filesystemactions.h"
#include "WorkMode.h"

//Инициализация главного окна приложения
CoreWindow::CoreWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CoreWindow)
{
    PrepairFileSpace();

    ui->setupUi(this);
    QWidget::setWindowTitle("АРМ Сперциалиста");

    //Связка изменения выбранного элемента и функций обновления информации
    connect(ui->listWidget_project, &QListWidget::itemClicked, this, &CoreWindow::on_new_element_selected_project);
    connect(ui->listWidget_result, &QListWidget::itemClicked, this, &CoreWindow::on_new_element_selected_record);

    ui->tableWidget_project->resizeColumnsToContents();
    ui->tableWidget_result->resizeColumnsToContents();
}

CoreWindow::~CoreWindow()
{
    delete ui;
}

//Создание окна создания нового проекта теста
void CoreWindow::on_pushButton_create_new_clicked()
{
    TestCreatorWindow window;
    window.setModal(true);
    window.exec();
}

//Создание окна редактирования проекта теста, если он существует
void CoreWindow::on_pushButton_open_redactor_clicked()
{
    if (ui->listWidget_project->currentItem() != nullptr)
    {
        TestCreatorWindow window (nullptr, ui->listWidget_project->currentItem()->text());
        window.setModal(true);
        window.exec();
    }
}

//Обновление содержимого списка проектов, проеверяется директория соседствующая с исполняемым файлом програмы
void CoreWindow::on_pushButton_update_project_clicked()
{
    ui->listWidget_project->clear();

    //Получение информации о проектах
    QFileInfoList fileList = ViewDirectory(WorkMode::TEST_PROJECTS);

    //Вывод названий проектов в списке
    auto iter = fileList.begin();
    while (iter != fileList.end())
    {
        QString fileName = iter->fileName().replace(".usertestfile", "");
        ui->listWidget_project->addItem(fileName);
        iter += 1;
    }
}

//Открытие директории, содержащей файлы проектов
void CoreWindow::on_pushButton_directory_project_clicked()
{
    OpenDirectory(WorkMode::TEST_PROJECTS);
}

//Обновление подробной информации о проекте при смене текущего элемента списка
void CoreWindow::on_new_element_selected_project()
{
    //Получение информации какой проект выбран
    QString whatClicked = ui->listWidget_project->currentItem()->text();

    //Чтение информации из файла проекта
    QStringList fileContent = ReadFile(WorkMode::TEST_PROJECTS, whatClicked);

    //Вывод информации о проекте
    auto iter = fileContent.begin();
    for (int i = 0; i < fileContent.count() || i < 4; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(*iter);
        ui->tableWidget_project->setItem(0, i, item);
        iter++;
    }
    ui->tableWidget_project->resizeColumnsToContents();
}

//Обновление содержимого списка записей тестирования, проеверяется директория соседствующая с исполняемым файлом програмы
void CoreWindow::on_pushButton_update_record_clicked()
{
    ui->listWidget_result->clear();

    //Получение информации о записях
    QFileInfoList fileList = ViewDirectory(WorkMode::RESULT_RECORDS);

    //Вывод названий записей в списке
    auto iter = fileList.begin();
    while (iter != fileList.end())
    {
        QString fileName = iter->fileName().replace(".userresultrecord", "");
        ui->listWidget_result->addItem(fileName);
        iter += 1;
    }
}

//Открытие директории, содержащей файлы записей тестирования
void CoreWindow::on_pushButton_directory_result_clicked()
{
    OpenDirectory(WorkMode::RESULT_RECORDS);
}

//Обновление подробной информации о записи тестирования при смене текущего элемента списка
void CoreWindow::on_new_element_selected_record()
{
    //Получение информации какая запись выбрана
    QString whatClicked = ui->listWidget_result->currentItem()->text();

    //Чтение информации из файла записи
    QStringList fileContent = ReadFile(WorkMode::RESULT_RECORDS, whatClicked);

    //Вывод информации о тестировании
    auto iter = fileContent.begin();
    for (int i = 0; i < fileContent.count() || i < 4; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(*iter);
        ui->tableWidget_result->setItem(0, i, item);
        iter++;
    }
    ui->tableWidget_result->resizeColumnsToContents();
}

//Старые функции
//Stub function, no tester programm yet, will be chanched to correct function of starting executable testing host

void CoreWindow::on_action_start_testing_triggered()
{
    QStringList fileContent;
    QString filename = "TestRecordTest";

    fileContent.append("TestName");
    fileContent.append("SolverName");
    fileContent.append("33");
    fileContent.append("89%");

    CreateFile(WorkMode::RESULT_RECORDS, filename, fileContent);
}

