#pragma once

#include <QMainWindow>
#include "forbesparticipant.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /**
     * @brief showRichestForbesParticipant - слот, который устанавливает имя
     * самого богатого миллиардера в LineEdit
     */
    void showRichestForbesParticipant();

private:
    Ui::MainWindow *ui;
    QVector<ForbesParticipant> forbesParticipants;  // Контейнер миллиардеров
};
