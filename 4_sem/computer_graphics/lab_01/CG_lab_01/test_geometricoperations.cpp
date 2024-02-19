#include <QTest>
#include <geometricoperations.h>
#include "test_geometricoperations.h"

bool Test_Geometricoperations::lineEquationIsEqual(QVector3D eq_1, QVector3D eq_2)
{
    if (eq_1.x() < 0 && eq_2.x() > 0)
    {
        eq_1 *= -1;
    }
    eq_1.normalize();
    eq_2.normalize();
    bool equal = true;
    equal = equal && qFuzzyCompare(eq_1.x(), eq_2.x());
    equal = equal && qFuzzyCompare(eq_1.y(), eq_2.y());
    equal = equal && qFuzzyCompare(eq_1.z(), eq_2.z());
    return equal;
}

Test_Geometricoperations::Test_Geometricoperations(QObject *parrent)
    : QObject(parrent)
{
}

void Test_Geometricoperations::test_getLineEquation()
{
    QVector3D equation;
    QPointF p1(0,0);
    QPointF p2(0,1);
    QPointF p3(1,0);
    QPointF p4(1,1);
    QPointF p5(2,2);
    QCOMPARE(getLineEquation(p2,p1,equation), OK);
    QVERIFY(lineEquationIsEqual(QVector3D(1,0,0), equation));

    QCOMPARE(getLineEquation(p1,p3,equation), OK);
    QVERIFY(lineEquationIsEqual(QVector3D(0,1,0), equation));

    QCOMPARE(getLineEquation(p1,p4,equation), OK);
    QVERIFY(lineEquationIsEqual(QVector3D(-1,1,0), equation));

    QCOMPARE(getLineEquation(p4,p5,equation), OK);
    QVERIFY(lineEquationIsEqual(QVector3D(-1,1,0), equation));

    QCOMPARE(getLineEquation(p1,p1,equation), ERR_SAME_POINT);
}
