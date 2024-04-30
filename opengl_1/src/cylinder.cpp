#include "cylinder.h"

/**
 * @brief Cylinder::Cylinder Default constructor builds cylinder to preset size
 */
Cylinder::Cylinder()
{
    r = 0.5;
    angle = 0.5;
    height = 2;
    sectors = 25;
    posit = QVector3D(0.0f,0.0f,0.0f);
    theta = 2*PI/sectors;
}

/**
 * @brief Cylinder::Cylinder Cylinder constructor
 * @param baseRadius radius of the smaller end
 * @param angle opening angle
 * @param height cylinder height
 * @param sectors number of horizontal and vertical sectors for the cylinder
 * @param position position of the center of the base of the cylinder
 */
Cylinder::Cylinder(float baseRadius, float angle, float height, int sectors, QVector3D position)
    : r(baseRadius), angle(angle), height(height), sectors(sectors),posit(position)
{
    theta = 2*PI/sectors;
}

/**
 * @brief Cylinder::initCylinder Initializes the vertex array for the cylinder.
 */
void Cylinder::initCylinder(){
    computeCylinder();
}

void Cylinder::setSectors(int sectors){
    sectors = sectors;
    theta = 2*PI/sectors;
    computeCylinder();
}
void Cylinder::setRadius(float radius){
    r = radius;
    computeCylinder();
}
void Cylinder::setAngle(float angle){
    this->angle = angle;
    computeCylinder();
}
void Cylinder::setHeight(float height){
    this->height = height;
    computeCylinder();
}
void Cylinder::setPosit(QVector3D position){
    posit = position;
    computeCylinder();
}

/**
 * @brief Cylinder::computeCylinder computes the vertex array for the cylinder.
 */
void Cylinder::computeCylinder(){
    vertexArr.clear();
    Vertex v1, v2, v3, v4;
    float hDelta = height/sectors;
    float r0, r1 = r;
    float h0, h1 = 0;
    for(size_t j=0;j<sectors;j++){
        // transition to next layer
        h0 = h1;
        h1 += hDelta;
        r0 = r1;
        r1 = r + h1*tan(angle);
        for(size_t i=0;i<sectors;i++){
            // Calculate vertices of a quad of the cylinder
            v1 = calcCircleBound(posit, r0, theta*i, h0);
            v2 = calcCircleBound(posit, r1, theta*i, h1);
            v3 = calcCircleBound(posit, r0, theta*(i+1), h0);
            v4 = calcCircleBound(posit, r1, theta*(i+1), h1);
            // Add vertices to array
            vertexArr.append(v1);
            vertexArr.append(v4);
            vertexArr.append(v2);
            vertexArr.append(v1);
            vertexArr.append(v3);
            vertexArr.append(v4);
        }
    }
    qDebug() << "done";
}

/**
 * @brief Cylinder::calcCircleBound Calculates a point at a layer (circle) of the cylinder and its normal
 * @param posit Cylinder position
 * @param r radius of circle at h
 * @param theta rotation angle
 * @param h height
 * @return Vertex of circle at height h and direction of angle
 */
Vertex Cylinder::calcCircleBound(QVector3D posit, float r1, float theta, float h) {
    // point position
    QVector3D p = QVector3D();
    p.setX(posit.x() + r1*cos(theta));
    p.setY(posit.y() + r1*sin(theta));
    p.setZ(posit.z() + h);

    float a = h + r1*tan(angle); // sphere height
    QVector3D q = posit; // sphere center
    q.setZ(posit.z()+a);
    QVector3D n = (q-p).normalized(); // direction of the normal

    return Vertex(p, n);
}
