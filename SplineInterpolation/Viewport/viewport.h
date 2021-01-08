#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QOpenGLWidget>
#include <QColor>

#include "Camera/camera.h"
#include "ObjectToDraw/objecttodraw.h"

class Viewport : public QOpenGLWidget
{
    Q_OBJECT
public:
    Viewport(Camera *camera, QWidget *parent = nullptr);
    void addObject(ObjectToDraw *objectToDraw);
protected:
    void initializeGL() override;
    void resizeGL(qint32 width, qint32 height) override;
    void paintGL() override;
private:
    QColor m_backgroundColor = QColorConstants::Gray;
    Camera *m_camera;
    QVector<ObjectToDraw *> m_objectsToDraw;
};

#endif // VIEWPORT_H
