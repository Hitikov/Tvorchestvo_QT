#include "testcreatorwindow.h"
#include "ui_testcreatorwindow.h"

#include "filesystemactions.h"
#include <QDateTime>

//Инициализация окна редактора
TestCreatorWindow::TestCreatorWindow(QWidget *parent, QString fileName) :
    QDialog(parent),
    ui(new Ui::TestCreatorWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Создание файла проекта");

    //Проверка получения названия проекта, открытие если поле названия не пустое
    if (fileName != "")
    {
        QWidget::setWindowTitle("Изменение файла проекта");
        ui->Button_CreateStub->setText("Сохранить изменения");
        fileContent = ReadFile(WorkMode::TEST_PROJECTS, fileName);
        setFileContent(fileName);
    }
}

TestCreatorWindow::~TestCreatorWindow()
{
    delete ui;
}

//Чтение содержимого файла, если при инициализации было получено не пустое название проекта
void TestCreatorWindow::setFileContent(QString fileName)
{
    //Если файл пустой, завершение функции
    if (fileContent.size() == 0)
        return;

    //Получение содержимого файла в соответствующие поля и переменные
    auto iter = fileContent.begin();

    ui->filename->setText(fileName); //Название файла
    ui->filename->setEnabled(false);

    ui->testname->setText(*iter); //Название теста
    ++iter;

    ui->creatorname->setText(*iter); //Имя создателя
    iter += 3;

    //Заголовки вопросов и их содержание
    while (iter != fileContent.end())
    {
        ui->questionlist->addItem(*iter);
        ++iter;
        QuestionsContent[ui->questionlist->item(ui->questionlist->count() - 1)].first = *iter;
        ++iter;
        QuestionsContent[ui->questionlist->item(ui->questionlist->count() - 1)].second = *iter;
        ++iter;
    }

    ui->questionlist->setCurrentItem(ui->questionlist->item(0));
}

//Создание файла с введенными параметрами
void TestCreatorWindow::on_Button_CreateStub_clicked()
{
    //Если поле названия файла проекта пустое, отмена создания файла
    if (ui->filename->text().isEmpty())
    {
        return;
    }

    //Получение информации из соответствующих полей и переменных
    QString filename = ui->filename->text(); //Название файла

    QString Dt = QDateTime::currentDateTime().toString();
    QStringList fileContent;

    //Название теста
    if (ui->testname->text().isEmpty())
        fileContent.push_back("Noname");
    else
        fileContent.push_back(ui->testname->text());

    //Имя создателя
    if (ui->creatorname->text().isEmpty())
        fileContent.push_back("Noname");
    else
        fileContent.push_back(ui->creatorname->text());

    fileContent.push_back(Dt); //Время создания

    fileContent.push_back(QString::number(ui->questionlist->count())); //Количество вопросов

    //Заголовки вопросов и их содержание
    for (int i = 0; i < ui->questionlist->count(); i++)
    {
        QString questionTitle = ui->questionlist->item(i)->text();
        fileContent.push_back(questionTitle);
        fileContent.push_back(QuestionsContent[ui->questionlist->item(i)].first);
        fileContent.push_back(QuestionsContent[ui->questionlist->item(i)].second);
    }

    //Вызов функции создания/обновления файла
    CreateFile(WorkMode::TEST_PROJECTS, filename, fileContent);

    this->close();
}

//Отмена создания файла
void TestCreatorWindow::on_ButtonHalt_clicked()
{
    this->close();
}

//Создание нового вопроса, переключение на него в списке вопросов
void TestCreatorWindow::on_ButtonCreateQuestion_clicked()
{
    ui->questionlist->addItem("NewQuestion");
    ui->questionlist->setCurrentItem(ui->questionlist->item(ui->questionlist->count() - 1));
}

//Удаление выбранного вопроса, переключение на первый в списке, если еще остались вопросы
void TestCreatorWindow::on_ButtonDeleteQuestion_clicked()
{
    if (ui->questionlist->currentItem() != nullptr)
    {
        ui->questionlist->model()->removeRow(ui->questionlist->currentRow());
        ui->questionlist->removeItemWidget(ui->questionlist->currentItem());
    }
    if (ui->questionlist->count() != 0) ui->questionlist->setCurrentItem(ui->questionlist->item(0));
}

//Реакция на обновление содежимого текстового поля содержания вопроса
void TestCreatorWindow::on_questioncontent_textChanged()
{
    //Обновление информации в словаре содержимого вопросов
    QuestionsContent[ui->questionlist->currentItem()].first = ui->questioncontent->toPlainText();
}

//Реакция на обновление содежимого текстового поля ответов
void TestCreatorWindow::on_questionanswers_textChanged()
{
    //Обновление информации в словаре содержимого вопросов
    QuestionsContent[ui->questionlist->currentItem()].second = ui->questionanswers->toPlainText();
}

//Реакция на обновление содежимого текстового поля заголовка вопроса
void TestCreatorWindow::on_questionTitle_textChanged(const QString &arg1)
{
    //Обновление информации в списке вопросов
    ui->questionlist->currentItem()->setText(arg1);
}

//Реакция на изменение выбранного вопроса
void TestCreatorWindow::on_questionlist_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    Q_UNUSED(previous)

    //Проверка на отстутствие информации в словаре, если содержимое остутствует запись пустой строки
    if (QuestionsContent[current].first.isNull()) QuestionsContent[current].first = "";
    if (QuestionsContent[current].second.isNull()) QuestionsContent[current].second = "";
    //Изменение текущего поля содержимого вопроса на сохраненное
    ui->questioncontent->setText(QuestionsContent[current].first);
    //Изменение текущего поля ответов на сохраненное
    ui->questionanswers->setText(QuestionsContent[current].second);
    //Изменение текущего поля заголовка вопроса на сохраненное
    ui->questionTitle->setText(current->text());
}
