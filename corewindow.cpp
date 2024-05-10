#include "corewindow.h"
#include "ui_corewindow.h"
#include "testcreatorwindow.h"
#include "testingexecution.h"
#include "filesystemactions.h"

CoreWindow::CoreWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CoreWindow)
{
    ui->setupUi(this);
    PrepairFileSpace();
}

CoreWindow::~CoreWindow()
{
    delete ui;
}

void CoreWindow::on_pushButton_create_new_clicked()
{
    TestCreatorWindow window;
    window.setModal(true);
    window.exec();
}

void CoreWindow::on_pushButton_open_redactor_clicked()
{
    ui->statusbar->showMessage(ui->listWidget_project->currentItem()->text());
}

void CoreWindow::on_pushButton_update_project_clicked()
{
    ui->listWidget_project->addItem("Проверка добавления");
}


void CoreWindow::on_pushButton_directory_project_clicked()
{

}

