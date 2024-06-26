#ifndef COREWINDOW_H
#define COREWINDOW_H

#include <QMainWindow>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class CoreWindow; }
QT_END_NAMESPACE

class CoreWindow : public QMainWindow
{
    Q_OBJECT

public:
    CoreWindow(QWidget *parent = nullptr);
    ~CoreWindow();

private slots:
    void on_pushButton_create_new_clicked();

    void on_pushButton_open_redactor_clicked();

    void on_pushButton_update_project_clicked();

    void on_pushButton_directory_project_clicked();

    void on_new_element_selected_project();

    void on_pushButton_update_record_clicked();

    void on_pushButton_directory_result_clicked();

    void on_new_element_selected_record();

    void on_action_start_testing_triggered();

private:
    Ui::CoreWindow *ui;
};
#endif // COREWINDOW_H
