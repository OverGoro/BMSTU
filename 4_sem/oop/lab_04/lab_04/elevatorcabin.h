#ifndef ELEVATORCABIN_H
#define ELEVATORCABIN_H

#include <QObject>
#include "elevatorcontroller.h"
#include "elevatordoor.h"

enum CabinState
{
    STOPPED,
    GOT_TARGET,
    MOVING
};

class ElevatorCabin : public QObject
{
    Q_OBJECT
public:
    explicit ElevatorCabin(QObject *parent = nullptr);
    ~ElevatorCabin() = default;

public slots:
    void getTargetSlot(ssize_t &targetFloor, ssize_t &currentFloor);
    void stoppedSlot(bool isLast, ssize_t currentFloor, ssize_t targetFloor = 1);

private slots:
    void _moveSlot();

signals:
    void _floorPassedSignal(ssize_t floor, Direction dir);
    void _openDoorsSignal();
    void _movingSignal();

private:
    void saveState(const ssize_t &targetFloor, const ssize_t &currentFloor);

protected:
    ElevatorDoor _door;
    ssize_t _currentFloor;
    ssize_t _targetFloor;
    Direction _direction;
    CabinState _status;
    bool _targetExist;

    QTimer _moveTimer;


};

#endif // ELEVATORCABIN_H
