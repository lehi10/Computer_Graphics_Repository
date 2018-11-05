#include <GL/glut.h>
#include "camera.h"
#include "vector_tools.h"

void DestroyCamera ( camera **theCamera )
{
    camera
    *thisCamera = *theCamera;
    if( ! thisCamera ) return;
    free( thisCamera );
    *theCamera = NULL;
}

camera *CreatePositionCamera( float positionX, float positionY, float positionZ )
{
    camera  *newCamera;
    int     ierr = 0;

    newCamera = (camera *) malloc( sizeof(camera) * 1 );

    newCamera->camViewX = positionX;
    newCamera->camViewY = positionY;
    newCamera->camViewZ = positionZ;

    // looks towards
    newCamera->camAtX = 0.0f;
    newCamera->camAtY = 0.0f;
    newCamera->camAtZ = 0.0f;

    newCamera->camUpX = 0.0f;
    newCamera->camUpY = 1.0f;
    newCamera->camUpZ = 0.0f;


    newCamera->camAperture  = 60.0f * DEGREE_TO_RAD;
    newCamera->camNear      = 0.5f;
    newCamera->camFar       = 200.0f;

    newCamera->camProjection    = CAM_CONIC;
    newCamera->aspectRatio      = 1.0f;

    SetDependentParametersCamera( newCamera );

    return newCamera;
}

void SetDependentParametersCamera (camera *thisCamera)
{
    // camera i j k vectors in world coordinates
    // camIX, camIY, camIZ;
    // camJX, camJY, camJZ;
    // camKX, camKY, camKZ;

    float   ix,   iy, iz;
    float   jx,   jy, jz;
    float   kx,   ky, kz;

    float   atX,  atY,  atZ;
    float   upX,  upY,  upZ;

    float   viewX,  viewY,   viewZ;
    int     ierr=0;

    viewX=  thisCamera->camViewX;
    viewY=  thisCamera->camViewY;
    viewZ=  thisCamera->camViewZ;

    atX=    thisCamera->camAtX;
    atY=    thisCamera->camAtY;
    atZ=    thisCamera->camAtZ;

    upX=    0.0f;
    upY=    1.0f;
    upZ=    0.0f;

    // i, j, k, up must be unit vectors
    // k = normalizar( AV )
    // i = normalizar( up ^ k )
    // j = k ^ i
    UnitVectorPP( &ierr, &kx, &ky, &kz, atX, atY, atZ, viewX, viewY, viewZ );
    UnitVectorVV( &ierr, &ix, &iy, &iz, upX, upY, upZ, kx, ky, kz );
    UnitVectorVV( &ierr, &jx, &jy, &jz, kx, ky, kz, ix, iy, iz );

    thisCamera->camKX = kx;
    thisCamera->camKY = ky;
    thisCamera->camKZ = kz;

    thisCamera->camIX = ix;
    thisCamera->camIY = iy;
    thisCamera->camIZ = iz;

    thisCamera->camJX = jx;
    thisCamera->camJY = jy;
    thisCamera->camJZ = jz;

    thisCamera->camUpX = jx;
    thisCamera->camUpY = jy;
    thisCamera->camUpZ = jz;
}


void SetGLCamera( camera *thisCamera )
{
    float fovy;
    glMatrixMode( GL_PROJECTION );
        glLoadIdentity( );

    if( thisCamera->camProjection == CAM_CONIC )
    {
        fovy = thisCamera->camAperture*RAD_TO_DEGREE;
        gluPerspective(fovy, thisCamera->aspectRatio, thisCamera->camNear, thisCamera->camFar );
    }
    else 
    { // CAM_PARALLEL
        glOrtho(thisCamera->x1, thisCamera->x2, thisCamera->y1, thisCamera->y2,
        thisCamera->z1,thisCamera->z2);
    }
    gluLookAt(thisCamera->camViewX, thisCamera->camViewY, thisCamera->camViewZ,
        thisCamera->camAtX, thisCamera->camAtY, thisCamera->camAtZ,
        thisCamera->camUpX, thisCamera->camUpY, thisCamera->camUpZ );
    glMatrixMode( GL_MODELVIEW ); //* GL_MODELVIEW *
}


void SetGLAspectRatioCamera( camera *thisCamera )
{
    GLint   viewport[4];
    glGetIntegerv( GL_VIEWPORT, viewport );
    if( viewport[3] > 0 )
        thisCamera->aspectRatio = (float) viewport[2] / (float) viewport[3];// width/height
    else
        thisCamera->aspectRatio = 1.0f;
    SetDependentParametersCamera( thisCamera );
}

void SetCamera( camera *thisCamera, 
                float viewX,    float viewY, float viewZ,
                float atX,  float atY,  float atZ,  
                float upX,  float upY,  float upZ )
{
    thisCamera->camViewX= viewX;
    thisCamera->camViewY= viewY;
    thisCamera->camViewZ= viewZ;

    thisCamera->camAtX =atX;
    thisCamera->camAtY =atY;
    thisCamera->camAtZ =atZ;

    thisCamera->camUpX =upX;
    thisCamera->camUpY =upY;
    thisCamera->camUpZ =upZ;

    SetDependentParametersCamera( thisCamera );
}



void AvanceFreeCamera(camera *thisCamera, float step) 
{
    float vaX, vaY, vaZ;
    vaX= step * thisCamera->camKX;
    vaY= step * thisCamera->camKY;
    vaZ= step * thisCamera->camKZ;
    // Set V & A

    thisCamera->camViewX=thisCamera->camViewX+vaX;
    thisCamera->camViewY=thisCamera->camViewY+vaY;
    thisCamera->camViewZ=thisCamera->camViewZ+vaZ;
    thisCamera->camAtX = thisCamera->camAtX + vaX;
    thisCamera->camAtY = thisCamera->camAtY + vaY;
    thisCamera->camAtZ = thisCamera->camAtZ + vaZ;
    SetDependentParametersCamera( thisCamera );
}

void YawCamera(camera *thisCamera, float angle)
{
    float vIn[3];
    vIn[0]=thisCamera->camAtX-thisCamera->camViewX;
    vIn[1]=thisCamera->camAtY-thisCamera->camViewY;
    vIn[2]=thisCamera->camAtZ-thisCamera->camViewZ;

    VectorRotY( vIn, angle );
    
    thisCamera->camAtX=thisCamera->camViewX+vIn[0];
    thisCamera->camAtY=thisCamera->camViewY+vIn[1];
    thisCamera->camAtZ=thisCamera->camViewZ+vIn[2];
    SetDependentParametersCamera( thisCamera );
}


void Rotar_Longitud(camera *thisCamera,float inc)
{
    float vIn[3];
    vIn[0]=thisCamera->camViewX-thisCamera->camAtX;
    vIn[1]=thisCamera->camViewY-thisCamera->camAtY;
    vIn[2]=thisCamera->camViewZ-thisCamera->camAtZ;
    
    VectorRotY( vIn, inc );

    thisCamera->camViewX=thisCamera->camAtX+vIn[0];
    thisCamera->camViewZ=thisCamera->camAtZ+vIn[2];
    
    SetDependentParametersCamera( thisCamera );
}

void Rotar_Latitud(camera *thisCamera,float inc)
{
    float vIn[3];
    vIn[0]=thisCamera->camViewX-thisCamera->camAtX;
    vIn[1]=thisCamera->camViewY-thisCamera->camAtY;
    vIn[2]=thisCamera->camViewZ-thisCamera->camAtZ;

    VectorRotXZ( vIn, inc, TRUE );

    thisCamera->camViewX=thisCamera->camAtX+vIn[0];
    thisCamera->camViewY=thisCamera->camAtY+vIn[1];
    thisCamera->camViewZ=thisCamera->camAtZ+vIn[2];

    SetDependentParametersCamera( thisCamera );
}

void PitchCamera( camera *thisCamera, float angle )
{
    float vIn[3];
    vIn[0]= thisCamera->camAtX - thisCamera->camViewX;
    vIn[1]= thisCamera->camAtY - thisCamera->camViewY;
    vIn[2]= thisCamera->camAtZ - thisCamera->camViewZ;
    VectorRotXZ( vIn, angle, TRUE );
    thisCamera->camAtX = thisCamera->camViewX + vIn[0];
    thisCamera->camAtY = thisCamera->camViewY + vIn[1];
    thisCamera->camAtZ = thisCamera->camViewZ + vIn[2];
    SetDependentParametersCamera( thisCamera );
}


void PanCamera( camera *thisCamera, float stepX, float stepY )
{
    float vaX, vaY, vaZ;
    vaX= stepX * thisCamera->camIX + stepY * thisCamera->camJX;
    vaY= stepX * thisCamera->camIY + stepY * thisCamera->camJY;
    vaZ= stepX * thisCamera->camIZ + stepY * thisCamera->camJZ;
    // Set V & A
    thisCamera->camViewX = thisCamera->camViewX + vaX;
    thisCamera->camViewY = thisCamera->camViewY + vaY;
    thisCamera->camViewZ = thisCamera->camViewZ + vaZ;
    thisCamera->camAtX = thisCamera->camAtX + vaX;
    thisCamera->camAtY = thisCamera->camAtY + vaY;
    thisCamera->camAtZ = thisCamera->camAtZ + vaZ;
    SetDependentParametersCamera( thisCamera );
}