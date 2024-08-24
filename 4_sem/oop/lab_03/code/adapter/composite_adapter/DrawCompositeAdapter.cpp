#include "DrawCompositeAdapter.h"
#include "DrawAdapterSolution.h"
#include "Exceptions.h"
void DrawCompositeAdapter::request()
{
    for (auto obj : *composite)
    {
        try
        {
            auto adapter = DrawAdapterSolution().create(obj, drawer, camera);
            adapter->request();
        }
        catch (NoSuitableAdapterException &e)
        {
        }
    }
}