//#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/intersect.hpp>
#include <stdio.h>

using namespace std;

#include <vector>
#include <map>
#include "PIG.h"


float eyex=0,eyey=3,eyez=10;


float pos[10] = {0,70,90,110,130,170,220,260,290,320};
float raio[10] = {25,2,4,5,3,10,8,6,5,2};
float angulo[10] = {0,0,0,0,0,0,0,0,0,0};
float vel[10] = {0,3,2,5,7,4,2,3.5,2.7,5.8};
int i;
int giro = 0;

GLUquadric *quad;
GLuint texturas[10];

void Luz(float amb){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    GLfloat pos[] = {0,0,0,5.0};

    glPushMatrix();
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,1);
    glLightfv(GL_LIGHT0,GL_POSITION,pos);
    glPopMatrix();

    GLfloat ambi[] = {amb,amb,amb,1.0};
    glLightfv(GL_LIGHT1,GL_AMBIENT,ambi);
}

void DesenhaPlaneta(){

    for (i=0;i<10;i++){
        glBindTexture(GL_TEXTURE_2D,texturas[i]);
        glPushMatrix();
        if (i==0){
            glScalef(-1,-1,-1);  //INVERTE AS FACES DO SOL
        }
        glRotatef(90,1,0,0);
        glRotatef(angulo[i],0,0,1);
        glTranslatef(pos[i]/10,0,0);
        gluSphere(quad,raio[i]/10,30,30);
        glTranslatef(-pos[i]/10,0,0);
        glPopMatrix();
    }
}

void DesenhaSkybox(float x,float y,float z,GLuint texts[]){


    float lado = 200.0;
    //glPushMatrix();
    //glTranslatef(x,y,z);
    float tam = 0.25;

    glColor3f(1.0,1.0,1.0);
    //glEnable(GL_TEXTURE_2D);
    //glDisable(GL_LIGHTING);
    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texts[0]);
    //        glActiveTexture(GL_TEXTURE0);
    glBegin(GL_QUADS);
        //frente
            glNormal3f(0.0,0.0, 1.0);

            glTexCoord2f(0.0,1.0);glVertex3f(-lado, -lado,  -lado);
            glTexCoord2f(0.0,0.0);glVertex3f(-lado, lado,  -lado);
            glTexCoord2f(1.0,0.0);glVertex3f(lado, lado,  -lado);
            glTexCoord2f(1.0,1.0);glVertex3f(lado, -lado,  -lado);
    glEnd();

    glBindTexture(GL_TEXTURE_2D,texts[1]);
    glBegin(GL_QUADS);
            //tras
            //glBindTexture(GL_TEXTURE_2D,texture[1]);
            //glColor4f(0.0,1.0,0.0,alfa);
            glNormal3f(0.0,0.0,-1.0);
            //glActiveTexture(GL_TEXTURE1);


            glTexCoord2f(1.0,1.0);glVertex3f(-lado, -lado,  lado);
            glTexCoord2f(1.0,0.0);glVertex3f(-lado, lado,  lado);
            glTexCoord2f(0.0,0.0);glVertex3f(lado, lado,  lado);
            glTexCoord2f(0.0,1.0);glVertex3f(lado, -lado,  lado);
glEnd();
glBindTexture(GL_TEXTURE_2D,texts[3]);
    glBegin(GL_QUADS);

            //direita
            //glBindTexture(GL_TEXTURE_2D,texture[2]);
            //glColor4f(0.0,0.0,1.0,alfa);
            glNormal3f(-1.0,0.0,0.0);
            //glActiveTexture(GL_TEXTURE2);

            glTexCoord2f(0.0,0.0);glVertex3f(lado, lado,  -lado);
            glTexCoord2f(0.0,1.0);glVertex3f(lado, -lado,  -lado);
            glTexCoord2f(1.0,1.0);glVertex3f(lado, -lado,  lado);
            glTexCoord2f(1.0,0.0);glVertex3f(lado, lado,  lado);

glEnd();
glBindTexture(GL_TEXTURE_2D,texts[2]);
    glBegin(GL_QUADS);

            //esquerda
            //glBindTexture(GL_TEXTURE_2D,texture[3]);
            //glColor4f(1.0,1.0,0.0,alfa);

            //glActiveTexture(GL_TEXTURE3);
            glNormal3f(1.0,0.0,0.0);
            glTexCoord2f(0.0,1.0);glVertex3f(-lado, -lado,  lado);
            glTexCoord2f(1.0,1.0);glVertex3f(-lado, -lado,  -lado);
            glTexCoord2f(1.0,0.0);glVertex3f(-lado, lado,  -lado);
            glTexCoord2f(0.0,0.0);glVertex3f(-lado, lado,  lado);
glEnd();
glBindTexture(GL_TEXTURE_2D,texts[4]);
    glBegin(GL_QUADS);
            //cima
            //glBindTexture(GL_TEXTURE_2D,texture[4]);
            //glColor4f(0.0,1.0,1.0,alfa);

            //glActiveTexture(GL_TEXTURE4);
            glNormal3f(0.0,-1.0,0.0);
            glTexCoord2f(0.0,0.0);glVertex3f(-lado, lado,  lado);
            glTexCoord2f(0.0,1.0);glVertex3f(-lado, lado,  -lado);
            glTexCoord2f(1.0,1.0);glVertex3f(lado, lado,  -lado);
            glTexCoord2f(1.0,0.0);glVertex3f(lado, lado,  lado);

glEnd();
    glBindTexture(GL_TEXTURE_2D,texts[5]);
    glBegin(GL_QUADS);
            //baixo
            //glBindTexture(GL_TEXTURE_2D,texture[5]);
            //glColor4f(1.0,0.0,1.0,alfa)

            //glActiveTexture(GL_TEXTURE5);
            glNormal3f(0.0,1.0,0.0);
            glTexCoord2f(0.0,0.0);glVertex3f(-lado, -lado,  lado);
            glTexCoord2f(1.0,0.0);glVertex3f(-lado, -lado,  -lado);
            glTexCoord2f(1.0,1.0);glVertex3f(lado, -lado,  -lado);
            glTexCoord2f(0.0,1.0);glVertex3f(lado, -lado,  lado);

    glEnd();
    //glPopMatrix();
    //glEnable(GL_LIGHTING);
    //glDisable(GL_TEXTURE_2D);

}

GLuint LoadPNGTextures(char *str ){

    GLuint idText;

    /* Create storage space for the texture */
    SDL_Surface *TextureImage = IMG_Load( str );

    printf("criei1b\n");

    /* Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit */
    if ( TextureImage ){

	    /* Create The Texture */
	    glGenTextures( 1, &idText );
	    printf("criei2b\n");

	    /* Typical Texture Generation Using Data From The Bitmap */
	    glBindTexture( GL_TEXTURE_2D, idText );

	    /* Generate The Texture */
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureImage->w,
			  TextureImage->h, 0, GL_RGBA,
			  GL_UNSIGNED_BYTE, TextureImage->pixels );
        printf("criei3b\n");

		glGetError();

	    /* Linear Filtering */
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        printf("criei4b\n");
	    glGenerateMipmap(GL_TEXTURE_2D);
        printf("criei5b\n");
    }
    else{
        printf("erro\n");
        printf("IMG_Load: %s\n", IMG_GetError());
    }

    /* Free up any memory we may have used */
    if ( TextureImage )
	    SDL_FreeSurface( TextureImage );

    return idText;
}

GLuint LoadBMPTextures(char *str ){

    GLuint idText;

    /* Create storage space for the texture */
    SDL_Surface *TextureImage = IMG_Load( str );

    printf("criei1a\n");

    /* Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit */
    if ( TextureImage ){

	    /* Create The Texture */
	    glGenTextures( 1, &idText );
	    printf("criei2a\n");

	    /* Typical Texture Generation Using Data From The Bitmap */
	    glBindTexture( GL_TEXTURE_2D, idText );

	    /* Generate The Texture */
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureImage->w,
			  TextureImage->h, 0, GL_BGR,
			  GL_UNSIGNED_BYTE, TextureImage->pixels );
        printf("criei3a\n");

		glGetError();

	    /* Linear Filtering */
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        printf("criei4a\n");
	    glGenerateMipmap(GL_TEXTURE_2D);
        printf("criei5a\n");
    }
    else{
        printf("erro\n");
        printf("IMG_Load: %s\n", IMG_GetError());
    }

    /* Free up any memory we may have used */
    if ( TextureImage )
	    SDL_FreeSurface( TextureImage );

    return idText;
}


void setup3d(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0,1.0,0.1,500.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_BLEND);
}

void setup2d(){

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(0, LARG_TELA, ALT_TELA, 0, -1, 1);

glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

glDisable(GL_DEPTH_TEST);
//glDisable(GL_LIGHTING);
//glDisable(GL_BLEND);
}


int main( int argc, char* args[] )
{
    PIG_Evento evento;
    PIG_Teclado meuTeclado;

    CriaJogo("Sistema Solar");
    meuTeclado = GetTeclado();

    glewInit();

    float brilho = 0.3;

    bool painel = false;

    glEnable(GL_TEXTURE_2D);

    texturas[0] = LoadPNGTextures(".//imagens//sol.png");
    texturas[1] = LoadPNGTextures(".//imagens//merc.png");
    texturas[2] = LoadPNGTextures(".//imagens//venus.png");
    texturas[3] = LoadPNGTextures(".//imagens//terra.png");
    texturas[4] = LoadPNGTextures(".//imagens//marte.png");
    texturas[5] = LoadPNGTextures(".//imagens//jupiter.png");
    texturas[6] = LoadPNGTextures(".//imagens//saturno.png");
    texturas[7] = LoadPNGTextures(".//imagens//uranus.png");
    texturas[8] = LoadPNGTextures(".//imagens//nept.png");
    texturas[9] = LoadPNGTextures(".//imagens//plutao.png");


    GLuint skybox[6];
    skybox[0] = LoadBMPTextures(".//imagens//frente.png");
    skybox[1] = LoadBMPTextures(".//imagens//tras.png");
    skybox[2] = LoadBMPTextures(".//imagens//esq.png");
    skybox[3] = LoadBMPTextures(".//imagens//dir.png");
    skybox[4] = LoadBMPTextures(".//imagens//topo.png");
    skybox[5] = LoadBMPTextures(".//imagens//chao.png");




    quad = gluNewQuadric();
    gluQuadricTexture(quad,true);

    GLuint idFrase=0;
    system("cls");
    float angHor=0,angVer=0;
    while (JogoRodando()!=0)
    {

        evento = GetEvento();

        if (meuTeclado[TECLA_ESQUERDA]){
            angHor -= 1;
        }else if (meuTeclado[TECLA_DIREITA]){
            angHor += 1;
        }else if(meuTeclado[TECLA_CIMA]){
            eyex += sin((angHor)*M_PI/180.0)*0.1f;
            eyez -= cos((angHor)*M_PI/180.0)*0.1f;
        }else if(meuTeclado[TECLA_BAIXO]){
            eyex -= sin((angHor)*M_PI/180.0)*0.1f;
            eyez += cos((angHor)*M_PI/180.0)*0.1f;
        }else if(meuTeclado[TECLA_KP_2]){
            angVer += 2.5f;
        }else if (meuTeclado[TECLA_BARRAESPACO]){
            if (!giro){
                giro = 1;
            }
            else{
                giro = 0;
            }
        }else if (meuTeclado[TECLA_z]){
            eyey+=0.1;
        }else if (meuTeclado[TECLA_x]){
            eyey-=0.1;
        }else if (meuTeclado[TECLA_q]){
            brilho+=0.1;
        }else if (meuTeclado[TECLA_w]){
            brilho-=0.1;
        }

        if (giro){
            for (i=0;i<10;i++){
                angulo[i]+=vel[i]/10;
                if (angulo[i] > 360){
                    angulo[i]-=360;
                }
            }
        }

        glEnable(GL_DEPTH_TEST);
        glClearColor(1,0,0,1);
        IniciaDesenho();



        angVer -= 0.5f;
        if (angVer<0)
            angVer = 0;

        //ajusta para 3d
        setup3d();



        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(angHor,0,1,0);
        glRotatef(angVer, cos((angHor)*M_PI/180.0), 0.0,sin((angHor)*M_PI/180.0));

        glTranslatef(-eyex,-eyey,-eyez);



        //desenha o planeta
        DesenhaPlaneta();
        Luz(brilho);

        //desenha o skybox
        glPushMatrix();

        glTranslatef(eyex,eyey,eyez);
        DesenhaSkybox(eyex,eyey,eyez,skybox);
        glPopMatrix();

        EncerraDesenho();
    }

    FinalizaJogo();
    return 0;
}
