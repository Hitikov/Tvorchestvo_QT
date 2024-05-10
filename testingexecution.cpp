#include "testingexecution.h"
#include "ui_testingexecution.h"

TestingExecution::TestingExecution(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestingExecution)
{
    ui->setupUi(this);
}

TestingExecution::~TestingExecution()
{
    delete ui;
}
