#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGLWidgets>
class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent = nullptr);
private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
signals:
    void initializeGL_signal();
    void resizeGL_signal(int w, int h);
    void paintGL_signal();
};

#endif // GLWIDGET_H
