#ifndef ELEVATORCONTROLLER_H
#define ELEVATORCONTROLLER_H

#include <QWidget>
#include <QGridLayout>
#include <vector>
#include <QDebug>
#include <memory>

#include "elevatorbutton.h"

#define FLOOR_COUNT 9
#define DOORS_TIME  500
#define MOVING_TIME 800

enum Direction
{
    DOWN = -1,
    STOP = 0,
    UP = 1
};


class ElevatorController : public QWidget
{
    Q_OBJECT;
    enum ControllerStatus
    {
        FREE,
        GOT_TARGET,
        BUSY
    };
public:
    explicit ElevatorController(QWidget *parent = nullptr);
    ~ElevatorController() = default;

public slots:
    void newTargetSlot(ssize_t floor);
    void floorPassedSlot(ssize_t floor, Direction direction);
    void controllerStoppedSlot();

signals:
    void controllerStoppedSignal();
    void cabinStoppedSignal(bool, ssize_t, ssize_t = 1);
    void getTargetSignal(ssize_t &targetFloor, ssize_t &_currentFloor);
    void floorPassedSignal(ssize_t floor, Direction direction);
    void targetReachedSignal(ssize_t floor);

private:
    bool targetExist(ssize_t &newFloor);

    ControllerStatus _state;
    Direction _direction;
    ssize_t _currentFloor;
    ssize_t _targetFloor;

    std::vector<std::shared_ptr<ElevatorButton>> elevator_buttons;
    std::vector<std::shared_ptr<ElevatorButton>> floor_buttons;

    std::vector<bool> _visitedFloors;
    std::unique_ptr<QVBoxLayout> _layout;
};

#endif // ELEVATORCONTROLLER_H
