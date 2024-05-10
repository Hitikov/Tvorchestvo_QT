#ifndef TESTCREATORWINDOW_H
#define TESTCREATORWINDOW_H

#include <QDialog>

namespace Ui {
class TestCreatorWindow;
}

class TestCreatorWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TestCreatorWindow(QWidget *parent = nullptr);
    ~TestCreatorWindow();

private:
    Ui::TestCreatorWindow *ui;
};

#endif // TESTCREATORWINDOW_H
