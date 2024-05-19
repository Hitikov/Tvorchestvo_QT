#ifndef TESTCREATORWINDOW_H
#define TESTCREATORWINDOW_H

#include <QDialog>
#include <QMap>
#include <QListWidget>

namespace Ui {
class TestCreatorWindow;
}

class TestCreatorWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TestCreatorWindow(QWidget *parent = nullptr, QString fileName = "");
    ~TestCreatorWindow();

private slots:
    void on_Button_CreateStub_clicked();

    void on_ButtonHalt_clicked();

    void on_ButtonCreateQuestion_clicked();

    void on_ButtonDeleteQuestion_clicked();

    void on_questioncontent_textChanged();

    void on_questionlist_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_questionTitle_textChanged(const QString &arg1);

    void on_questionanswers_textChanged();

private:
    void setFileContent(QString fileName);

    Ui::TestCreatorWindow *ui;

    QStringList fileContent;

    QMap<QListWidgetItem*, QPair<QString, QString>> QuestionsContent;
};

#endif // TESTCREATORWINDOW_H
