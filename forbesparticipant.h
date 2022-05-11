#pragma once

#include <QString>

// Участник списка Forbes
struct ForbesParticipant
{
    ForbesParticipant(const QString& _name, int _countBillions);

    QString name;           // Имя
    quint16 countBillions;  // Колличество миллиардов
};


