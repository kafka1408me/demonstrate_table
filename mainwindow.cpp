#include <QSpinBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Список имен колонок: имя и денежное состояние
    QStringList columnNames {"Name", "Money, billions"};

    // Добавляем миллиардеров в список
    forbesParticipants.push_back(ForbesParticipant("Elon Musk", 219));
    forbesParticipants.push_back(ForbesParticipant("Jeff Bezos", 171));
    forbesParticipants.push_back(ForbesParticipant("Sergey Brin", 107));
    forbesParticipants.push_back(ForbesParticipant("Artem Avetisyan", 500));

    // Количество колонок = количеству имен колонок
    ui->forbesTable->setColumnCount(columnNames.size());
    // Количество строк таблицы равно количеству миллиардеров в контейнере
    ui->forbesTable->setRowCount(forbesParticipants.size());

    // Устанавливаем названия колонок
    ui->forbesTable->setHorizontalHeaderLabels(columnNames);

    // Перебираем всех богачей т добавляем их в таблицу
    int i = 0;  // номер строки в таблице
    // auto& billionaire преобразуется в ForbesParticipant& - ссылка на объект класса ForbesParticipant
    for(auto& billionaire: forbesParticipants)
    {
        // Добавляем в колонку имя миллиардера в первую колонку строки таблицы
        ui->forbesTable->setCellWidget(i, 0, new QLabel(billionaire.name));
        QSpinBox* spbx = new QSpinBox;
        spbx->setMaximum(1000);  // Максимальное количество денег у человека
        spbx->setValue(billionaire.countBillions);
        // Добавляем спинбокс во вторую колонку строки
        ui->forbesTable->setCellWidget(i, 1, spbx);

        // соединяем сигнал с лямбда-функцией!
        // static_cast нужен, потому что есть два сигнала: QSpinBox::valueChanged(int) и QSpinBox::valueChanged(const QString &) и
        // нужно использовать именно QSpinBox::valueChanged(int).
        // шаблон лямбда-функции: [](){} . В [] указываем захватываемые переменные - эти переменные можно будет использовать внутри лямбды.
        // Если в [] ничего не указать, то все используемые внутри лямбды внешние переменные будут захвачены по значению
        // (т.е. скопированы). В () указываем параметры (как у обычной функции).
        // &billionaire - & перед именем переменной означает захват по ссылке
        connect(spbx, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this, &billionaire](int value){
            billionaire.countBillions = value;
            this->showRichestForbesParticipant();  // this здесь необязателен
        });
        ++i;  // Увеличиваем номер строки
    }

    // Запрещаем пользователю редактировать LineEdit
    ui->richestParticipantLineEdit->setReadOnly(true);

    // Находим и выводим имя богатейшего человека из списка
    showRichestForbesParticipant();

    // Устанавливаем надпись для окна
    setWindowTitle("Forbes list");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showRichestForbesParticipant()
{
    // Итератор на объект богатейшего человека
    auto richest = forbesParticipants.cbegin();
    // перебираем миллиардеров, начиная со второго
    for(auto it = forbesParticipants.cbegin() + 1, end = forbesParticipants.cend(); it != end; ++it)
    {
        // Сравниваем состояние миллиардеров
        if(it->countBillions > richest->countBillions)
        {
            richest = it;
        }
    }

    // Устанавливаем имя богатейшего человека
    ui->richestParticipantLineEdit->setText(richest->name);
}

