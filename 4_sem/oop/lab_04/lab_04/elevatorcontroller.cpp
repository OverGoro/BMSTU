#include "elevatorcontroller.h"
#include "qlabel.h"

ElevatorController::ElevatorController(QWidget *parent) : QWidget(parent)
{
    _layout = std::unique_ptr<QVBoxLayout>(new QVBoxLayout(this));

    QHBoxLayout* labelsLayout = new QHBoxLayout();
    QGridLayout* gridLayout = new QGridLayout();

    QLabel* elevatorLabel = new QLabel("Кнопки в лифте", this);
    QLabel* floorsLabel = new QLabel("Кнопки на этажах", this);

    elevatorLabel->setStyleSheet("QLabel {"
                                 "color: white;" // Белый цвет текста
                                 "background-color: #2e86c1;" // Цвет фона
                                 "text-align: center;"
                                 "font-size: 12px;" // Размер шрифта
                                 "font-weight: bold;" // Жирный текст
                                 "border: 2px solid #1f618d;" // Рамка
                                 "border-radius: 5px;" // Скругление углов
                                 "min-width: 80px;"
                                 "padding: 6px;" // Внутренний отступ
                                 "}");

    // Установка стилей для метки "Кнопки на этажах"
    floorsLabel->setStyleSheet("QLabel {"
                               "color: white;" // Белый цвет текста
                               "background-color: #27ae60;" // Цвет фона
                               "text-align: center;"
                               "font-size: 12px;" // Размер шрифта
                               "font-weight: bold;" // Жирный текст
                               "border: 2px solid #1e8449;" // Рамка
                               "border-radius: 5px;" // Скругление углов
                               "min-width: 80px;"
                               "padding: 6px;" // Внутренний отступ
                               "}");

    labelsLayout->addWidget(elevatorLabel);
    labelsLayout->addWidget(floorsLabel);

    _layout->addLayout(labelsLayout);
    _layout->addLayout(gridLayout);

    QObject::connect(this, &ElevatorController::floorPassedSignal,
                     this, &ElevatorController::floorPassedSlot);

    QObject::connect(this, &ElevatorController::controllerStoppedSignal,
                     this, &ElevatorController::controllerStoppedSlot);

    _state = FREE;
    _currentFloor = 1;
    _targetFloor = 1;
    _direction = STOP;

    for (int i = 0; i < FLOOR_COUNT; i++)
    {
        std::shared_ptr<ElevatorButton> btn1(new ElevatorButton);
        btn1->setFloor(FLOOR_COUNT - i);
        btn1->setText(QString::number(FLOOR_COUNT - i));

        std::shared_ptr<ElevatorButton> btn2(new ElevatorButton);
        btn2->setFloor(FLOOR_COUNT - i);
        btn2->setText(QString::number(FLOOR_COUNT - i));

        elevator_buttons.insert(elevator_buttons.begin(), btn1);
        floor_buttons.insert(floor_buttons.begin(), btn2);

        gridLayout->addWidget(btn1.get(), i, 0);
        gridLayout->addWidget(btn2.get(), i, 1);

        _visitedFloors.push_back(true);
        _visitedFloors.push_back(true);

        connect(btn1.get(), &ElevatorButton::pressSignal, this, &ElevatorController::newTargetSlot);
        connect(btn2.get(), &ElevatorButton::pressSignal, this, &ElevatorController::newTargetSlot);
    }

    this->setLayout(_layout.get());
}



void ElevatorController::newTargetSlot(ssize_t floor)
{
    _visitedFloors[floor - 1] = false;

    if (_state != GOT_TARGET)
    {
        _state = GOT_TARGET;
        targetExist(floor);
        _targetFloor = floor;

        if (_currentFloor == _targetFloor)
            emit floorPassedSignal(_currentFloor, _direction);
        else
        {
            _direction = _targetFloor > _currentFloor ? UP : DOWN;
            emit getTargetSignal(_targetFloor, _currentFloor);
        }
    }
}

void ElevatorController::controllerStoppedSlot()
{
    if (_state == BUSY)
    {
        _state = FREE;
        emit cabinStoppedSignal(true, _currentFloor);
    }
}

void ElevatorController::floorPassedSlot(ssize_t floor, Direction direction)
{
    if (_state == GOT_TARGET || _state == BUSY)
    {
        _state = BUSY;
        _currentFloor = floor;
        _direction = direction;

        if (_currentFloor == _targetFloor)
        {
            emit floor_buttons[floor - 1]->unpressSignal();
            emit elevator_buttons[floor - 1]->unpressSignal();
            _visitedFloors[floor - 1] = true;

            if (targetExist(_targetFloor))
                emit cabinStoppedSignal(false, _currentFloor, _targetFloor);
            else
                emit controllerStoppedSignal();
        }
    }
}

bool ElevatorController::targetExist(ssize_t &newFloor)
{
    int direction = _direction != STOP ? _direction : DOWN;

    for (int i = _currentFloor - 1; i >= 0 && i < FLOOR_COUNT; i += direction)
    {
        if (!_visitedFloors[i])
        {
            newFloor = i + 1;
            return true;
        }
    }

    for (int i = _currentFloor - 1; i >= 0 && i < FLOOR_COUNT; i += -direction)
    {
        if (!_visitedFloors[i])
        {
            newFloor = i + 1;
            return true;
        }
    }

    return false;
}
