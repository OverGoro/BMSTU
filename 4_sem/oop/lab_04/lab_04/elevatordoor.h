#ifndef ELEVATORDOOR_H
#define ELEVATORDOOR_H

#include <QObject>
#include <QDebug>
#include <QTimer>

enum ElevatorDoorStatus
{
    OPEN,
    OPENING,
    CLOSING,
    CLOSED
};

class ElevatorDoor : public QObject
{
    Q_OBJECT;
public:
    ElevatorDoor();
    ~ElevatorDoor() = default;

public slots:
    void openingSlot();
private slots:
    void openedSlot();
    void closingSlot();
    void closedSlot();
signals:
    void closedSignal();

private:
    ElevatorDoorStatus _status;

    QTimer _openingTimer;
    QTimer _closingTimer;
    QTimer _openedTimer;
};

#endif // ELEVATORDOOR_H
