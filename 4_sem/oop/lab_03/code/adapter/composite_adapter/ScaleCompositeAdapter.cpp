#include "ScaleCompositeAdapter.h"
#include "TransformAdapterSolution.h"
#include "Exceptions.h"
#include "ScaleAdapterSolution.h"
void ScaleCompositeAdapter::request()
{
    for (auto obj : *composite)
    {
        try
        {
            auto adapter = ScaleAdapterSolution().create(obj, std::make_shared<ScaleParams>(params));
            adapter->request();
        }
        catch (NoSuitableAdapterException &e)
        {
        }
    }
}