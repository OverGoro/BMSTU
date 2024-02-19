#ifndef TEST_GEOMETRICOPERATIONS_H
#define TEST_GEOMETRICOPERATIONS_H

#include <QObject>

class Test_Geometricoperations : public QObject
{
    Q_OBJECT
private:
    bool lineEquationIsEqual(QVector3D eq_1, QVector3D eq_2);
public:
    explicit Test_Geometricoperations(QObject *parrent = NULL);
private slots:

    void test_getLineEquation();
};

#endif // TEST_GEOMETRICOPERATIONS_H
