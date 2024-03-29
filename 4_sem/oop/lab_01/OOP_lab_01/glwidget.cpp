#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    :QOpenGLWidget(parent)
{

}

void GLWidget::initializeGL()
{
    glClearColor(1,1,1,0);
    glColor3f(0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void GLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    double aspect_ratio = static_cast<double>(w) / static_cast<double>(h);
    double fov = 45.0; // Угол обзора

    QMatrix4x4 projection;
    projection.perspective(fov, aspect_ratio, 0.1, 100.0); // Настройка перспективной проекции
    projection.lookAt({0,0,-5}, {0,0,0}, {0,1,0});

    glMultMatrixf(projection.constData());

    glViewport(0, 0, w, h);
    emit resizeGL_signal(w, h);
}

void GLWidget::paintGL()
{
    emit paintGL_signal();
}

