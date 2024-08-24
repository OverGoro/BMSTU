#ifndef CAMERACOMMAND_H
#define CAMERACOMMAND_H

#include <memory>
#include <cstddef>

#include "basecommand.h"

using ID = std::shared_ptr<std::size_t>;

class CameraCommand : public BaseCommand
{
};

class AddCamera : public CameraCommand
{
public:
    AddCamera(const Point &position, const Point &direction, const Point &up,
              double x_fov, double y_fov, double screen_distantion)
        : position(position), direction(direction), up(up),
        _x_fov(x_fov), _y_fov(y_fov), _screen_distantion(screen_distantion){};

    virtual void execute() override;
    std::shared_ptr<BaseCommand> clone() const override;

private:
    Point position;
    Point direction;
    Point up;
    double _x_fov;
    double _y_fov;
    double _screen_distantion;
};

class DeleteCamera : public CameraCommand
{
public:
    DeleteCamera(const std::size_t id);

    virtual void execute() override;
    std::shared_ptr<BaseCommand> clone() const override;

private:
    std::size_t _id;
};

class MoveCamera : public CameraCommand
{
public:
    MoveCamera(const double dx, const double dy, const double dz, const std::size_t id);

    virtual void execute() override;
    std::shared_ptr<BaseCommand> clone() const override;

private:
    double _dx, _dy, _dz;
    std::size_t _id;
};

class RotateCamera : public CameraCommand
{
public:
    RotateCamera(const double ax, const double ay, const double az, const std::size_t id);

    virtual void execute() override;
    std::shared_ptr<BaseCommand> clone() const override;

private:
    double _ax, _ay, _az;
    std::size_t _id;
};

class SetCamera : public CameraCommand
{
public:
    explicit SetCamera(const std::size_t id);

    virtual void execute() override;
    std::shared_ptr<BaseCommand> clone() const override;

private:
    std::size_t _id;
};

#endif // CAMERACOMMAND_H
