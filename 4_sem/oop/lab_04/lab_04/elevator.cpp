#include "elevator.h"

Elevator::Elevator(QObject *parent) : QObject(parent)
{
    _controller.setStyleSheet("background-color:green;");

    connect(&_cabin, &::ElevatorCabin::_floorPassedSignal,
            &_controller, &ElevatorController::floorPassedSlot);

    connect(&_controller, &ElevatorController::getTargetSignal,
            &_cabin, &ElevatorCabin::getTargetSlot);

    connect(&_controller, &ElevatorController::cabinStoppedSignal,
            &_cabin, &ElevatorCabin::stoppedSlot);

}

QWidget *Elevator::widget()
{
    return &_controller;
}
