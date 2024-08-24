#include "RotateCompositeAdapter.h"
#include "TransformAdapterSolution.h"
#include "Exceptions.h"
#include "RotateAdapterSolution.h"
void RotateCompositeAdapter::request()
{
    for (auto obj : *composite)
    {
        try
        {
            auto adapter = RotateAdapterSolution().create(obj, std::make_shared<RotateParams>(params));
            adapter->request();
        }
        catch (NoSuitableAdapterException &e)
        {    

        }
    }
}