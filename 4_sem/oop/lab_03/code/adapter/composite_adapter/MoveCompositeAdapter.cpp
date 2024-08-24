#include "MoveCompositeAdapter.h"
#include "TransformAdapterSolution.h"
#include "Exceptions.h"
#include "MoveAdapterSolution.h"
void MoveCompositeAdapter::request()
{
    for (auto obj : *composite)
    {
        try
        {
            auto adapter = MoveAdapterSolution().create(obj, std::make_shared<MoveParams>(params));
            adapter->request();
        }
        catch (NoSuitableAdapterException &e)
        {    

        }
    }
}