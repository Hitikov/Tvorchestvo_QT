#ifndef TESTINGEXECUTION_H
#define TESTINGEXECUTION_H

#include <QDialog>

namespace Ui {
class TestingExecution;
}

class TestingExecution : public QDialog
{
    Q_OBJECT

public:
    explicit TestingExecution(QWidget *parent = nullptr);
    ~TestingExecution();
private:
    Ui::TestingExecution *ui;
};

#endif // TESTINGEXECUTION_H
