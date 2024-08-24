#ifndef MODELSCOMMAND_H
#define MODELSCOMMAND_H


#include <cstddef>
#include <memory>

#include "basecommand.h"


using ID = std::shared_ptr<std::size_t>;

class ModelsCommand : public BaseCommand { };

class MoveModels : public ModelsCommand
{
public:
    MoveModels(const double dx, const double dy, const double dz);

    virtual void execute() override;
    std::shared_ptr<BaseCommand> clone() const override;

private:
    double _dx, _dy, _dz;
};



class ScaleModels : public ModelsCommand
{
public:
    ScaleModels(const double kx, const double ky, const double kz);

    virtual void execute() override;
    std::shared_ptr<BaseCommand> clone() const override;

private:
    double _kx, _ky, _kz;
};



class RotateModels : public ModelsCommand
{
public:
    RotateModels(const double ox, const double oy, const double oz);

    virtual void execute() override;
    std::shared_ptr<BaseCommand> clone() const override;

private:
    double _ox, _oy, _oz;
};

#endif // MODELSCOMMAND_H
