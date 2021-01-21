#include "viewport.h"

#include <QDebug>
#include <QOpenGLFunctions>

#define DEBUG

Viewport::Viewport(Camera *camera, const QColor& a_backgroundColor, QWidget *parent)
    : QOpenGLWidget(parent), m_backgroundColor(a_backgroundColor), m_camera(camera) {}

void Viewport::initializeGL() {}

void Viewport::resizeGL(qint32 width, qint32 height)
{
#ifdef DEBUG
    qDebug() << "Viewport::resizeGL"
             << "w: " << width
             << "h: " << height;
#endif

    QOpenGLFunctions *currentContext = QOpenGLContext::currentContext()->functions();

    currentContext->glViewport(0, 0, width, height);

    m_camera->setSize(width, height);
}

void Viewport::paintGL()
{
    QOpenGLFunctions *currentContext = QOpenGLContext::currentContext()->functions();

    currentContext->glClearColor(m_backgroundColor.redF(), m_backgroundColor.greenF(),
                 m_backgroundColor.blueF(), m_backgroundColor.alphaF());
    currentContext->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    quint64 size = m_objectsToDraw.size();

    QMatrix4x4 viewMatrix = m_camera->viewMatrix();

    for(quint64 i = 0; i < size; ++i)
    {
        m_objectsToDraw[i]->draw(viewMatrix);
    }
}

void Viewport::wheelEvent(QWheelEvent *event)
{
#ifdef DEBUG
    qDebug() << "Viewport::wheelEvent " << event << "\n\tmod: "<< event->modifiers();
#endif

    QPoint angel = event->angleDelta();

    if(event->modifiers() == Qt::ControlModifier)
    {
        m_camera->scaling(QVector3D(1 + 0.001 * angel.y(), 1 + 0.001 * angel.y(), 1));
    }

    this->update();
}

void Viewport::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key::Key_W:
        m_camera->transferring(QVector3D(0, -m_NormalTransferSpeed, 0));
        break;
    case Qt::Key::Key_S:
        m_camera->transferring(QVector3D(0, m_NormalTransferSpeed, 0));
        break;
    case Qt::Key::Key_A:
        m_camera->transferring(QVector3D(m_NormalTransferSpeed, 0, 0));
        break;
    case Qt::Key::Key_D:
        m_camera->transferring(QVector3D(-m_NormalTransferSpeed, 0, 0));
        break;

    case Qt::Key::Key_E:
        m_camera->rotation(-m_NormalRotateSpeed);
        break;
    case Qt::Key::Key_Q:
        m_camera->rotation(m_NormalRotateSpeed);
        break;
    }

    this->update();
}

void Viewport::animate()
{
    quint64 size = m_objectsToDraw.size();

    for(quint64 i = 0; i < size; ++i)
    {
        m_objectsToDraw[i]->animate();
    }

    update();
}

void Viewport::addObject(ObjectToDraw *objectToDraw)
{
    m_objectsToDraw.push_back(objectToDraw);
}
