#ifndef CAMERA_H
#define CAMERA_H
#define CAM_PARALLEL 1
#define CAM_CONIC 2
#define CAM_TRIPODE 3
#define CAM_PAN 4
#define CAM_STOP 0
#define CAM_EXAMINAR 1
#define CAM_PASEAR 2

typedef struct _Camera
{
	// we consider a rigth handed reference system for the camera
	// V point where the camera is placed (world coordinates)
	// A point the camera is looking at	(world coordinates)

	// up vector : unit vector, perpendicular to AV (world componnents)
	// origin camera reference system : at V
	// Z camera : defined by vector from A to V (penetrates the viewer’s eye)
	// Y camera : defined by up vector
	// X camera : looking from V towards A goes rigthwards
	float camViewX; // View point
	float camViewY;
	float camViewZ;
	
	float camAtX;
	float camAtY;	// look At point
	float camAtZ;
	
	float camUpX;
	float camUpY;	// Up vector
	float camUpZ;
	float camAperture; // field of view radians
	// NOTE : OpenGL uses degrees
	// defined as they are used by OpenGL
	// always => positive ; Far > Near (distance from plane to camera origin)
	float camNear;
	float camFar;
	int	camProjection; 	// PARALLEL or CONIC
	int camMovimiento; 	// EXAMINAR, ANDAR, TRIPODE or PAN

	// ****** dependent values ******
	// window system dependent
	float aspectRatio;

	// for ortho projection
	float x1, x2, y1, y2, z1, z2;

	// camera i j 	k vectors in world coordinates
	float camIX,camIY, camIZ;
	float camJX,camJY, camJZ;
	float camKX,camKY, camKZ;

}camera;


void DestroyCamera ( camera **theCamera );

camera *CreatePositionCamera( float positionX, float positionY, float positionZ );

void SetCamera( camera *thisCamera, 
				float viewX,	float viewY, 
				float viewZ,	float atX,	
				float atY,		float atZ,	
				float upX,		float upY,	
				float upZ );
	
void SetDependentParametersCamera( camera *thisCamera );
void SetGLCamera( camera *thisCamera );
void SetGLAspectRatioCamera( camera *thisCamera );

// Free camera advances "step" following vector VA, step admits negative values
void AvanceFreeCamera( camera *thisCamera, float step );

// ROTATION
void YawCamera( camera *thisCamera, float angle ); //local axis Y camera

void Rotar_Latitud( camera *thisCamera, float inc );
void Rotar_Longitud( camera *thisCamera, float inc );

//TRIPODE MODE

void PitchCamera( camera *thisCamera, float angle ); // eje Z de la camara
void PanCamera( camera *thisCamera, float stepX, float stepY );


#endif /* CAMERA_H */
