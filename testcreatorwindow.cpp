#include "testcreatorwindow.h"
#include "ui_testcreatorwindow.h"

TestCreatorWindow::TestCreatorWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestCreatorWindow)
{
    ui->setupUi(this);
}

TestCreatorWindow::~TestCreatorWindow()
{
    delete ui;
}
