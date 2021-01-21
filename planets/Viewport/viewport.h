#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QColor>

#include "Camera/camera.h"
#include "ObjectToDraw/objecttodraw.h"

#include <QWheelEvent>

class Viewport : public QOpenGLWidget
{
    Q_OBJECT
public:
    Viewport(Camera *camera, const QColor& a_backgroundColor = QColorConstants::Gray, QWidget *parent = nullptr);
    void addObject(ObjectToDraw *objectToDraw);
protected:
    void initializeGL() override;
    void resizeGL(qint32 width, qint32 height) override;
    void paintGL() override;

    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;
public slots:
    void animate();

private:
    qreal m_NormalTransferSpeed = 10;
    qreal m_NormalRotateSpeed = M_PI_4/50;
    QColor m_backgroundColor = QColorConstants::Gray;
    Camera *m_camera;
    QVector<ObjectToDraw *> m_objectsToDraw;
};

#endif // VIEWPORT_H
