#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <QVector3D>

class Camera
{
public:
    Camera(const qreal &a_width = 0, const qreal &a_hight = 0); // по умолчанию только потому что я использую qt ui

    void rotation(const qreal &angel);
    void transferring(const QVector3D &transferring);
    void scaling(const QVector3D &scaling);

    QMatrix4x4 viewMatrix();
    QMatrix4x4 clipMatrix();

    static QMatrix4x4 rotateMatrix(const qreal &angel);
    static QMatrix4x4 transferMatrix(const QVector3D &transferring);
    static QMatrix4x4 scaleMatrix(const QVector3D &scaling);

    void setSize(const qreal& a_width, const qreal& a_hight);

private:
    qreal m_width;
    qreal m_hight;
    QVector3D m_transfer = QVector3D(0,0,0);
    QVector3D m_scale = QVector3D(1,1,1);
    qreal m_rotate = 0;
};

#endif // CAMERA_H
