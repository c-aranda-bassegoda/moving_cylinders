#ifndef CYLINDER_H
#define CYLINDER_H

#include <QOpenGLDebugLogger>

#include "vertex.h"

class Cylinder
{
    float r, angle, height;

    float theta;
    constexpr static float PI = acos(-1.0f);
    
    QVector3D posit;
    float a0=0;
    float a1=1;

    int sectors = 20;
    QVector3D axisVector = QVector3D(0.0,0.0,1.0);
    QVector3D perpVector = QVector3D(1.0,0.0,0.0); // a vector perpendicular to the axis
    QVector<Vertex> vertexArr;
public:
    Cylinder();
    Cylinder(float baseRadius, float angle, float height, int sectors, QVector3D position);
    void initCylinder();

    void setSectors(int sectors);
    void setRadius(float radius);
    void setAngle(float angle);
    void setHeight(float height);
    void setPosit(QVector3D position);
    
    inline float getRadiusDerivativeWRTa() {return sin(angle);}
    inline float getRadiusAt(float a) {return r + a*tan(angle);}

    inline float getA0(){ return a0; }
    inline float getA1(){ return a1; }
    inline float getRadius(){ return r; }
    inline float getAngle(){ return angle; }
    inline float getHeight(){ return height; }

    inline QVector3D getPosition() {return posit; }

    inline QVector3D getAxisVector() {return axisVector; }
    inline QVector3D getVectorPerpToAxis() {return perpVector; }
    inline int getSectors(){ return sectors; }
    inline QVector<Vertex> getVertexArr(){ return vertexArr; }
private:
    void computeCylinder();
    Vertex calcCircleBound(QVector3D posit, float r1, float theta, float h);
};

#endif // CYLINDER_H
