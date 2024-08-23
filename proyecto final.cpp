//#include <gl/gl.h>     // The GL Header File
//#include <windows.h>	//Solo para Windows
//#include <GL/glut.h>   // The GL Utility Toolkit (Glut) Header
//#include <stdlib.h>		// Descomentar para Linux
//#include <stdio.h>
//#include <string.h>
//#include <malloc.h>		// Solo para Windows

#include "texture.h"
#include "figuras.h"
#include "Camera.h"

#include "cmodel/CModel.h"


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
static GLuint ciudad_display_list;	//Display List for the Monito


//NEW// Keyframes
float posX =0, posY = 2.5, posZ =-3.5, rotRodIzq = 0;
float giroMonito = 0;
float movBrazoDer = 0.0;
float movBrazoIzq = 0.0;

#define MAX_FRAMES 9
int i_max_steps = 90;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float salto;
	float saltoinc;
	
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex=5;			//introducir datos
bool play=false;
int playIndex=0;


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame=0,time,timebase=0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font=(int)GLUT_BITMAP_HELVETICA_18;

//Otras opciones son:
/*GLUT_BITMAP_8_BY_13
GLUT_BITMAP_9_BY_15
GLUT_BITMAP_TIMES_ROMAN_10
GLUT_BITMAP_TIMES_ROMAN_24
GLUT_BITMAP_HELVETICA_10
GLUT_BITMAP_HELVETICA_12
GLUT_BITMAP_HELVETICA_18*/


//LUCES
float transZ = -5.0f;
float transX = -2.0f;
float AnguloX = 0.0f;

float AnguloY = 0.0f;
float AnguloZ = 0.0f;
float transY = 0.0f;
int screenW = 0.0;
int screenH = 0.0;
float LightAngle = 30.0f;

bool	light = false;		// Luz ON/OFF
bool	positional = true;
static int spin = 0;


//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = {22};

GLfloat mat_diffusev[] = { 0.0, 1.0, 0.0, 1.0 };					// Object Color main 
GLfloat mat_diffusea[] = { 0.0, 0.0, 1.0, 1.0 };					// Object Color main 
GLfloat mat_diffuser[] = { 1.0, 0.0, 0.0, 1.0 };					// Object Color main 
GLfloat mat_diffuseb[] = { 1.0, 1.0, 1.0, 1.0 };					// Object Color main 
GLfloat mat_diffusef[] = { 1.0, 0.0, 1.0, 1.0 };					// Object Color main 
GLfloat mat_diffuseam[] = { 1.0, 1.0, 0.0, 1.0 };					// Object Color main 
GLfloat mat_diffusen[] = { 1.0, 0.5, 0.0, 1.0 };					// Object Color main 

GLfloat Posicion[]= { 0.0f, 0.0f, 0.0f, 1.0f };			// Light Position
GLfloat Posicion2[]= { 0.0f, 0.0f, -3.0f };				

GLfloat LightAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; 			// Ambient Light Values negro
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values blanco
GLfloat LightSpecular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values blanco

GLfloat LightPosicion[] = { 0.0f, 0.0f, 0.0f, 1.0f };			// Light Position 
GLfloat LightPosicion1[] = { 0.0f, 0.0f, 1.0f, 0.0f };			// Light Position
GLfloat LightDireccion[] = { 0.0f, 0.0f, -2.0f };			// Light Position		

GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };					// Color background

GLfloat mat_specular[] = { 0.0, 0.0, 1.0, 1.0 };				// Specular color
GLfloat mat_shininess[] = { 100.0 };							// brillo

 GLfloat mat_diffuse[] = { 0.9f, 0.7f, 0.4f, 1.0f };


CTexture text21;
CTexture text22;
CTexture text23;
CTexture text24;
CTexture text25;
CTexture text26;

CTexture text1;
CTexture text2;
CTexture text3;	
CTexture text4;	
CTexture text5;	
CTexture text6;	
CTexture text7;

CTexture tree;

CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto
CFiguras fig5;	//Casa01
CFiguras fig6;
CFiguras fig7;	//Para crear Monito

float angRot = 0.0;
float movKitX = 0.0;
float movKitZ = 0.0;
float rotKit = 0.0;
float rotTires = 0.0;
bool g_fanimacion = false;
bool g_avanza = false;

//ignora esto :V
bool circuito = false;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;
bool recorrido4 = false;
bool recorrido5 = false;

int timer = 0;

void ciudad ()  //ignora esto :V
{

		glPushMatrix(); //Camino1
			glTranslatef(23.5,0.0,0.0);
			glScalef(40,0.1,7);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Camino2
			glTranslatef(-23.5,0.0,0.0);
			glScalef(40,0.1,7);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
		
		glPushMatrix(); //Camino3  lateral derecho
			glTranslatef(47,0.0,-19);
			glRotatef(90, 0, 1, 0);
			//glScalef(40,0.1,7);
			glScalef(45,0.1,7);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Camino4  fondo derecho
			glTranslatef(21.75,0.0,-38);
			//glScalef(40,0.1,7);
			glScalef(43.5,0.1,7);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
		
		glPushMatrix(); //Camino5  fondo izquierdo
			glTranslatef(-21.75,0.0,-38);
			//glScalef(40,0.1,7);
			glScalef(43.5,0.1,7);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Camino6 lateral izquierdo
			glTranslatef(-47,0.0,-19);
			glRotatef(90, 0, 1, 0);
			//glScalef(40,0.1,7);
			glScalef(45,0.1,7);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();


		glPushMatrix(); //Pasto
			glTranslatef(0.0,0.0,-4.0);
			glScalef(87,0.1,1);
			glDisable(GL_LIGHTING);
			fig4.prisma2(text5.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Pasto
			glTranslatef(0.0,0.0,4.0);
			glScalef(87,0.1,1);
			glDisable(GL_LIGHTING);
			fig4.prisma2(text5.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Casa01
			glTranslatef(0.0,3.0,7.0);
			glRotatef(90,1,0,0);
			glRotatef(180,0,0,1);
			glScalef(6,5.0,6);
			glDisable(GL_LIGHTING);
			fig5.prisma2(text6.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Casa01
			glTranslatef(0.0,3.0,-7.0);
			glRotatef(90,1,0,0);
			//glRotatef(180,0,0,1);
			glScalef(6,5.0,6);
			glDisable(GL_LIGHTING);
			fig5.prisma2(text6.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();


		
}

void luces(void)
{
	//Configuracion luz
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);				// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);				// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);				// Setup The Diffuse Light

	glLightfv(GL_LIGHT1, GL_POSITION, Position);				// Position The Light
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Position2);			// Direction Of The Light
																//glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);			// Position The Light
																//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,LightDirection);	// Direction Of The Light


}


void cuad(float a, float b, float c)
{

	//glPushMatrix();

	glColor3f(a,b,c);
	glBegin(GL_QUADS);	//Front
			//glNormal3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(25.0f, 0.0f, 0.0f);
			glVertex3f(25.0f, 25.0f, 0.0f);
			glVertex3f(0.0f, 25.0f, 0.0f);
			
			
		glEnd();


	//glPopMatrix();
}


void cubo(float x, float y, float z, float color1, float color2, float color3)
{
	GLfloat vertice[8][3] = {
		{ x/2 , -y/2, z/2},    //V0
		{ -x/2, -y/2, z/2},    //V1
		{ -x/2, -y/2, -z/2},    //V2
		{ x/2, -y/2, -z/2},    //V3
		{ x/2, y/2, z/2},    //V4
		{ x/2, y/2, -z/2},    //V5
		{ -x/2, y/2, -z/2},    //V6
		{ -x/2, y/2, z/2},    //V7
	};

	glColor3f(color1, color2, color3);
	glBegin(GL_POLYGON);	//Front
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[4]);
		glVertex3fv(vertice[7]);
		glVertex3fv(vertice[1]);
	glEnd();

	glColor3f(color1, color2, color3);
	glBegin(GL_POLYGON);	//Right
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[3]);
		glVertex3fv(vertice[5]);
		glVertex3fv(vertice[4]);
	glEnd();

	glColor3f(color1, color2, color3);
	glBegin(GL_POLYGON);	//Back
		glVertex3fv(vertice[6]);
		glVertex3fv(vertice[5]);
		glVertex3fv(vertice[3]);
		glVertex3fv(vertice[2]);
	glEnd();

	glColor3f(color1, color2, color3);
	glBegin(GL_POLYGON);  //Left
		glVertex3fv(vertice[1]);
		glVertex3fv(vertice[7]);
		glVertex3fv(vertice[6]);
		glVertex3fv(vertice[2]);
	glEnd();

	glColor3f(color1, color2, color3);
	glBegin(GL_POLYGON);  //Bottom
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[1]);
		glVertex3fv(vertice[2]);
		glVertex3fv(vertice[3]);
	glEnd();

	glColor3f(color1, color2, color3);
	glBegin(GL_POLYGON);  //Top
		glVertex3fv(vertice[4]);
		glVertex3fv(vertice[5]);
		glVertex3fv(vertice[6]);
		glVertex3fv(vertice[7]);
	glEnd();
}

void cubotext(float a, float b, float c, GLuint textura1){
	GLfloat vertice [8][3] = {
				{a ,-b, c},    //Coordenadas Vértice 0 V0
				{-a ,-b, c},    //Coordenadas Vértice 1 V1
				{-a ,-b, -c},    //Coordenadas Vértice 2 V2
				{a ,-b, -c},    //Coordenadas Vértice 3 V3
				{a ,b, c},    //Coordenadas Vértice 4 V4
				{a ,b, -c},    //Coordenadas Vértice 5 V5
				{-a ,b, -c},    //Coordenadas Vértice 6 V6
				{-a ,b, c},    //Coordenadas Vértice 7 V7
				};


		glBindTexture(GL_TEXTURE_2D, textura1);   // choose the texture to use.
		glBegin(GL_POLYGON);	//Front
			//glColor3f(0.0,0.0,1.0);
			glNormal3f( 0.0f, 0.0f, 1.0f);

			glTexCoord2f(0.16f, 0.0f); glVertex3fv(vertice[0]);
			glTexCoord2f(0.16f, 0.5f); glVertex3fv(vertice[4]);
			glTexCoord2f(0.8f, 0.5f); glVertex3fv(vertice[7]);
			glTexCoord2f(0.8f, 0.0f); glVertex3fv(vertice[1]);
		glEnd();
	
		glBindTexture(GL_TEXTURE_2D, textura1);
		glBegin(GL_POLYGON);	//Right
			//glColor3f(0.0,0.0,1.0);
			glNormal3f( 1.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0, 0.5f); glVertex3fv(vertice[0]);
			glTexCoord2f(0.5f, 0.5f); glVertex3fv(vertice[3]);
			glTexCoord2f(0.5f, 1.0f); glVertex3fv(vertice[5]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[4]);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, textura1);
		glBegin(GL_POLYGON);	//Back
			//glColor3f(0.0,1.0,0.0);
			glNormal3f( 0.0f, 0.0f,-1.0f);
			glTexCoord2f(0.0f, 0.5f); glVertex3fv(vertice[6]);
			glTexCoord2f(0.5f, 0.5f); glVertex3fv(vertice[5]);
			glTexCoord2f(0.5f, 0.0f); glVertex3fv(vertice[3]);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[2]);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, textura1);
		glBegin(GL_POLYGON);  //Left
			//glColor3f(1.0,1.0,1.0);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.5f, 0.0f); glVertex3fv(vertice[1]);
			glTexCoord2f(0.5f, 0.5f); glVertex3fv(vertice[7]);
			glTexCoord2f(1.0f, 0.5f); glVertex3fv(vertice[6]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[2]);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, textura1);
		glBegin(GL_POLYGON);  //Bottom
			//glColor3f(0.4,0.2,0.6);
			glNormal3f( 0.0f,-1.0f, 0.0f);
			glTexCoord2f(0.75f, 0.33f); glVertex3fv(vertice[0]);
			glTexCoord2f(1.0f, 0.33f); glVertex3fv(vertice[1]);
			glTexCoord2f(1.0f, 0.66f); glVertex3fv(vertice[2]);
			glTexCoord2f(0.75f, 0.66f); glVertex3fv(vertice[3]);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, textura1);   // choose the texture to use.
		glBegin(GL_POLYGON);  //Top
			//glColor3f(0.8,0.2,0.4);
			glColor3f(1.0,1.0,1.0);
			glNormal3f( 0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.25, 0.33f); glVertex3fv(vertice[4]);
			glTexCoord2f(0.75, 0.33f); glVertex3fv(vertice[5]);
			glTexCoord2f(0.75, 0.66f); glVertex3fv(vertice[6]);
			glTexCoord2f(0.25f, 0.66f); glVertex3fv(vertice[7]);
		glEnd();
}

GLuint createDL() 
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL,GL_COMPILE);
	// call the function that contains 
	// the rendering commands
		ciudad();
		//monito();
	// endList
	glEndList();

	return(ciudadDL);
}
			
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);
	//Para construir la figura comentar esto
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Position2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);

	//glEnable ( GL_COLOR_MATERIAL );
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glPolygonMode(GL_BACK, GL_LINE);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE);			// Set The Blending Function For Translucency
    //glColor4f(1.0f, 1.0f, 1.0f, 0.5); 
    
   // text1.LoadBMP("01.bmp");

	text1.LoadTGA("cobre1.tga");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text2.LoadTGA("cobre2.tga");
	text2.BuildGLTexture();
	text2.ReleaseImage();

	text3.LoadTGA("cobre3.tga");
	text3.BuildGLTexture();
	text3.ReleaseImage();

	text4.LoadTGA("cobre4.tga");
	text4.BuildGLTexture();
	text4.ReleaseImage();

	text5.LoadTGA("metal1.tga");
	text5.BuildGLTexture();
	text5.ReleaseImage();

	text6.LoadTGA("metal2.tga");
	text6.BuildGLTexture();
	text6.ReleaseImage();

	text7.LoadTGA("verde.tga");
	text7.BuildGLTexture();
	text7.ReleaseImage();

	//ignora esto :V
	text21.LoadTGA("wall1.tga");
	text21.BuildGLTexture();
	text21.ReleaseImage();

	text21.LoadTGA("wall1.tga");
	text21.BuildGLTexture();
	text21.ReleaseImage();

	text21.LoadTGA("wall1.tga");
	text21.BuildGLTexture();
	text21.ReleaseImage();

	text21.LoadTGA("wall1.tga");
	text21.BuildGLTexture();
	text21.ReleaseImage();

	text22.LoadTGA("wall2.tga");
	text22.BuildGLTexture();
	text22.ReleaseImage();

	text23.LoadTGA("wall3.tga");
	text23.BuildGLTexture();
	text23.ReleaseImage();

	text24.LoadTGA("wall4.tga");
	text24.BuildGLTexture();
	text24.ReleaseImage();

	text25.LoadTGA("floor.tga");
	text25.BuildGLTexture();
	text25.ReleaseImage();

	text26.LoadTGA("ceiling.tga");
	text26.BuildGLTexture();
	text26.ReleaseImage();


	tree.LoadTGA("Tree.tga");
	tree.BuildGLTexture();
	tree.ReleaseImage();

	objCamera.Position_Camera(0,2.5f,3, 0,2.5f,0, 0, 1, 0);

	//NEW Crear una lista de dibujo
	ciudad_display_list = createDL();

	//NEW Iniciar variables de KeyFrames
	for(int i=0; i<MAX_FRAMES; i++)
	{
		KeyFrame[i].posX =0;
		KeyFrame[i].posY =0;
		KeyFrame[i].posZ =0;
		KeyFrame[i].incX =0;
		KeyFrame[i].incY =0;
		KeyFrame[i].incZ =0;
	}

	//NEW//////////////////NEW//////////////////NEW//////////////////

	KeyFrame[0].posX = 0.5;
	KeyFrame[0].posY = 0;
	KeyFrame[0].posZ = 0.6;

	KeyFrame[1].posX = 0.7;
	KeyFrame[1].posY = 0.25;
	KeyFrame[1].posZ = 0.7;

	KeyFrame[2].posX = 0.8;
	KeyFrame[2].posY = 0.5;
	KeyFrame[2].posZ = 0.8;

	KeyFrame[3].posX = 0.9;
	KeyFrame[3].posY = 0.5;
	KeyFrame[3].posZ = 0.9;

	KeyFrame[4].posX = 1;
	KeyFrame[4].posY = 0;
	KeyFrame[4].posZ = 1;

}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	
	glPushMatrix();

	glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
	

		glPushMatrix();		
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0,60,0);
				fig1.skybox(130.0, 130.0, 130.0,text21.GLindex, text22.GLindex, text23.GLindex, text24.GLindex, text25.GLindex, text26.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			/*glPushMatrix();//una plataforma
				glPushMatrix();  //PILAR DE SOSTENER
					glDisable(GL_LIGHTING);
					cubotext(2,8,2,text1.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix();  //PILAR DE SOSTENER
					glTranslatef(15,0,0);
					glDisable(GL_LIGHTING);
					cubotext(2,8,2,text1.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //base de metal
					glTranslatef(8,11,0);
					glDisable(GL_LIGHTING);
					cubotext(10,3,2,text5.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //base de metal2
					glTranslatef(8,2,0);
					glDisable(GL_LIGHTING);
					cubotext(6,1,0.5,text6.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //base de metal2
					glTranslatef(8,0.5,0);
					glDisable(GL_LIGHTING);
					cubotext(6,1,0.5,text6.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();*/

			glPushMatrix(); //segunda base
				glPushMatrix();  //PILAR DE SOSTENER
					glDisable(GL_LIGHTING);
					cubotext(2,20,2,text1.GLindex);//textura de cobre
					glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix();  //PILAR DE SOSTENER
					glTranslatef(20,0,0);
					glDisable(GL_LIGHTING);
					cubotext(2,20,2,text1.GLindex);//textura de cobre
					glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //base de metal
					glTranslatef(10,20,0);
					glDisable(GL_LIGHTING);
					cubotext(12,3,2,text5.GLindex); //textura de metal
					glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //viga1
					glTranslatef(10,5,0);
					glRotatef(45,0,0,1);
					glDisable(GL_LIGHTING);
					cubotext(12,1,0.5,text2.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //viga2
					glTranslatef(10,5,0);
					glRotatef(-45,0,0,1);
					glDisable(GL_LIGHTING);
					cubotext(12,1,0.5,text2.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();


			glPopMatrix();

			

			glPopMatrix();


				glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuser);
				glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
				glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
				/*glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuser);*/

		glPopMatrix();

	glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
			glColor3f(1.0,0.0,0.0);
			pintaTexto(-11,8.5,-14,(void *)font,s);
			glColor3f(1.0,1.0,1.0);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);

	glutSwapBuffers ( );

}

void animacion()
{

	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {

		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.2 );
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.2));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.4 );
			break;

		case 'u':
		case 'U':
			objCamera.UpDown_Camera( CAMERASPEED+0.4 );
			break;

		case 'n':
		case 'N':
			objCamera.UpDown_Camera(- (CAMERASPEED+0.4) );
			break;

					//Agregar aquí teclas para movimiento de luz
	case 'y':		//Movimientos de Luz
	case 'Y':
		spin = (spin - 20) % 360;
		break;
	case 'g':
	case 'G':
		spin = (spin + 20) % 360;
		break;;


	case 'h':   //Activamos/desactivamos luz
	case 'H':
		light = !light;
		if (light == 0)
			printf("apagada\n");
		else
			printf("prendida\n");
		break;

	case 'p':   //Activamos/desactivamos luz
	case 'P':
		positional = !positional;
		if (positional == 1)
			printf("spotlight\n");
		else
			printf("direccional\n");
		break;

	case 'c':
		LightAngle += 2.0f;
		printf("Angulo = %f\n", LightAngle);
		break;
	case 'v':
		LightAngle -= 2.0f;
		printf("Angulo = %f\n", LightAngle);

		case 'O':		//  
		case 'o':
				g_fanimacion^= true; //Activamos/desactivamos la animacíon
				circuito = false;
			break;

		case 'i':		//  
		case 'I':
				circuito^= true; //Activamos/desactivamos la animacíon
				g_fanimacion = false;
			break;

		case 'k':		//
		case 'K':
			if (FrameIndex<MAX_FRAMES)
			{
				printf("frameindex %d\n", FrameIndex);

				KeyFrame[FrameIndex].posX = posX;
				KeyFrame[FrameIndex].posY = posY;
				KeyFrame[FrameIndex].posZ = posZ;

				FrameIndex++;
			}
			
			break;

		case 'l':						
		case 'L':
			if(play==false && (FrameIndex>1))
			{

				posX = KeyFrame[0].posX;
				posY = KeyFrame[0].posY;
				posZ = KeyFrame[0].posZ;


				//First Interpolation
				KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;		//100 frames
				KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;		//100 frames
				KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;		//100 frames
			


				play = true;
				playIndex = 0;
				i_curr_steps = 0;
			}
			else
			{
				play=false;
			}
			break;

		/*case 'y':						
		case 'Y':
			posZ++;
			//printf("%f \n", posZ);
			break;

		case 'g':						
		case 'G':
			posX--;
			//printf("%f \n", posX);
			break;

		case 'h':						
		case 'H':
			posZ--;
			//printf("%f \n", posZ);
			break;

		case 'j':						
		case 'J':
			posX++;
			//printf("%f \n", posX);
			break;

		case 'b':						
			rotRodIzq++;
			//printf("%f \n", rotRodIzq);
			break;

		case 'B':						
			rotRodIzq--;
			//printf("%f \n", rotRodIzq);
			break;

		case 'p':						
			giroMonito++;
			//printf("%f \n", giroMonito);
			break;

		case 'P':						
			giroMonito--;
			//printf("%f \n", giroMonito);
			break;*/

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		//pos_camY -= 0.5f;
		//pos_cam.y += 0.5f;
		//eye_cam.y += 0.5f;
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		//pos_camY += 0.5f;
		//pos_cam.y -= 0.5f;
		//eye_cam.y -= 0.5f;
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}

int main ( int argc, char** argv )   // Main Function
{
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (500, 500);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Practica 12"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );
  glutMainLoop        ( );          // 

  return 0;
}
