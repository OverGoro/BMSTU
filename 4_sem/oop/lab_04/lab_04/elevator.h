#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>

#include "elevatorcontroller.h"
#include "elevatorcabin.h"

class Elevator : public QObject
{
    Q_OBJECT;
public:
    explicit Elevator(QObject *parent = nullptr);
    ~Elevator() = default;

    QWidget *widget();

private:
    ElevatorController _controller;
    ElevatorCabin _cabin;
};


#endif // ELEVATOR_H
