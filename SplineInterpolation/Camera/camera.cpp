#include <QtMath>

#include "camera.h"

#define DEBUG

void Camera::rotation(const qreal &a_rotate)
{
    m_rotate += a_rotate;
}

void Camera::transferring(const QVector3D &a_transfer)
{
    m_transfer += a_transfer;
}

void Camera::scaling(const QVector3D &a_scale)
{
    m_scale += a_scale;
}

QMatrix4x4 Camera::viewMatrix()
{
    QMatrix4x4 rotateMatrix = Camera::rotateMatrix(m_rotate);
    QMatrix4x4 transferMatrix = Camera::transferMatrix(m_transfer);
    QMatrix4x4 scaleMatrix = Camera::scaleMatrix(QVector3D(m_scale.x(), m_scale.y(), 1));

    QMatrix4x4 viewMatrix = transferMatrix * rotateMatrix * scaleMatrix;

    return viewMatrix;
}

QMatrix4x4 Camera::rotateMatrix(const qreal &angel)
{
    QMatrix4x4 Rotate;

    Rotate(0,0) = qCos(angel);
    Rotate(0,1) = -qSin(angel);

    Rotate(1,0) = qSin(angel);
    Rotate(1,1) = qCos(angel);

    return Rotate;
}

QMatrix4x4 Camera::transferMatrix(const QVector3D &transfer)
{
    QMatrix4x4 Transfer;

    for(int i = 0; i < 3; ++i)
    {
        Transfer(i, 3) = transfer[i];
    }

    return Transfer;
}

QMatrix4x4 Camera::scaleMatrix(const QVector3D &scale)
{
    QMatrix4x4 Scale;

    for(int i = 0; i < 3; ++i)
    {
        Scale(i, i) = scale[i];
    }

    return Scale;
}

void Camera::toOrigin()
{
    m_transfer = QVector3D(0,0,0);
    m_scale = QVector3D(1,1,1);
    m_rotate = 0;
}
