#include <stdio.h>
#include "vector_tools.h"

void VectorNormalize(int *ierr, float *vx, float *vy, float *vz) {
    float A, B, C;
    float modf;
    double mod;

    if (*ierr) return;

    A = *vx;
    B = *vy;
    C = *vz;
    mod = A * A + B * B + C*C;
    if (mod > VECTOR_EPSILON) {
        modf = (float) (1. / sqrt(mod));
        *vx = A * modf;
        *vy = B * modf;
        *vz = C * modf;
    } else {
        *vx = 0.0;
        *vy = 0.0;
        *vz = 1.0;
        *ierr = TRUE;
    }
}

void UnitVectorPP(int *ierr, float *wx, float *wy, float *wz,
        float ax, float ay, float az,
        float bx, float by, float bz) {
    // given two points SET a unit vector that goes from A to B
    if (*ierr) return;
    *wx = bx - ax;
    *wy = by - ay;
    *wz = bz - az;
    VectorNormalize(ierr, wx, wy, wz);
}

void UnitVectorVV(int *ierr, float *wx, float *wy, float *wz,
        float ux, float uy, float uz,
        float vx, float vy, float vz) {
    // Vector product : w = u ^ v
    if (*ierr) return;
    *wx = uy * vz - uz * vy;
    *wy = uz * vx - ux * vz;
    *wz = ux * vy - uy * vx;
    VectorNormalize(ierr, wx, wy, wz);
}

void VectorRotY(float *vIn, float inc) {
    float alpha;
    float modZX;
    float mod;

    //         __________________> X          
    //        |*          
    //        | *           
    //        |  *         
    //        |   *        
    //        |    *       
    //        |     *      
    //        |      *     
    //        | alpha *    
    //        |        *    
    //        v           
    //       Z      

    mod = MOD(vIn[0], vIn[1], vIn[2]);
    if (mod < VECTOR_EPSILON) return;
    vIn[0] = vIn[0] / mod;
    vIn[1] = vIn[1] / mod;
    vIn[2] = vIn[2] / mod;

    // if vector is too parallel to the "y" axis do nothing
    if (fabs(vIn[1]) > sin(PI_VALUE / 2.0 - ANGLE_EPSILON)) return;
    modZX = (float) sqrt(vIn[0] * vIn[0] + vIn[2] * vIn[2]);
    alpha = (float) acos(vIn[2] / modZX);
    if (vIn[0] < 0.0f) alpha = 2.0f * PI_VALUE - alpha;

    alpha += inc;
    vIn[0] = (float) sin(alpha) * modZX;
    vIn[2] = (float) cos(alpha) * modZX;

    vIn[0] = vIn[0] * mod;
    vIn[1] = vIn[1] * mod;
    vIn[2] = vIn[2] * mod;
}

void VectorRotXZ(float *vIn, float inc, int flagStop) {
    float alpha, beta;
    float mod;
    float maxAngle = 90.0f * DEGREE_TO_RAD - ANGLE_EPSILON;

    // Plane that contains the vector and the "y" axis
    //
    //      Y          
    //        ^          
    //        |          
    //        |          
    //        |        *  
    //        |       *   
    //        |      *    
    //        |     *     
    //        |    *      
    //        |   *       
    //        |  *        
    //        | *  beta
    //        |*          
    //         ------------------> X-Z          
    //         

    mod = MOD(vIn[0], vIn[1], vIn[2]);
    if (mod < VECTOR_EPSILON) return;
    vIn[0] = vIn[0] / mod;
    vIn[1] = vIn[1] / mod;
    vIn[2] = vIn[2] / mod;

    // if vector is too parallel to the "y" axis do nothing
    if (fabs(vIn[1]) > sin(maxAngle)) return;

    // 1 Compute alpha & beta	
    alpha = (float) acos(vIn[2] / sqrt(vIn[0] * vIn[0] + vIn[2] * vIn[2]));
    if (vIn[0] < 0.0f) alpha = 2.0f * PI_VALUE - alpha;

    // hypotenuse must be always 1.0 (because v is a unit vector)
    // first we measure beta from X-Z up to our vector
    // the result will be among -90 and +90
    beta = (float) asin(vIn[1]);

    // 2 ConstantIncrement beta (two possibilities)
    if (flagStop) {
        // when beta goes further than pi/2 or -pi/2 => stop avoiding a vertical position
        beta += inc;
        if (beta > maxAngle) beta = maxAngle;
        else if (beta < -maxAngle) beta = -maxAngle;
    } else {
        // to keep a constant rotation direction inc must be a positive value
        if (alpha > PI_VALUE) beta += inc;
        else beta -= inc;
    }

    // 3 Compute new vector	
    vIn[0] = (float) cos(beta) * (float) sin(alpha);
    vIn[1] = (float) sin(beta);
    vIn[2] = (float) cos(beta) * (float) cos(alpha);

    vIn[0] = vIn[0] * mod;
    vIn[1] = vIn[1] * mod;
    vIn[2] = vIn[2] * mod;
}