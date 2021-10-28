//-----------------------------------------
//    TRABALHO 3 - COMPUTACAO GRAFICA
//    POR IGOR FRANCA
//    27/out/2021
//-----------------------------------------

#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <vector>

// Variáveis Globais
char texto[30];
GLfloat win, r, g, b, r_1 = 0.0f, g_1 = 0.0f, b_1=1.0f, fAspect;
GLfloat r_2 = 1.0f, g_2 = 0.0f, b_2 = 0.0f;
GLfloat x_1 = 0.0, x_2 = 12.0, y_1 = -120.0, y_2 = -108.0;
GLint view_w, view_h, dados;
char vida = '3';
int resultado = 1;

// Desenha texto na tela
void DesenhaTexto(char *string, int x, int y)
{
  	glPushMatrix();
        // Posição no universo onde o texto será colocado
        glRasterPos2f(x, y);
        // Exibe caracter a caracter
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*string++);
	glPopMatrix();
}

// Desenhas as linhas limites do labirinto
void desenhaLinhas(void)
{

    //Barra vermelha
    glBegin(GL_QUAD_STRIP);
        glColor3f(r_2,g_2,b_2);
        glVertex3f(-20, 112, 0);
        glVertex3f(-20, 102, 0);
        glVertex3f(20, 112, 0);
        glVertex3f(20, 102, 0);
    glEnd();
    // Extremidades
    // Ponto 1
    glColor3f(r, g, b);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-100, 100);
        glVertex2f(-20, 100);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(20, 100);
        glVertex2f(100, 100);
    glEnd();
    // Ponto 2 -- nao muda
    glBegin(GL_LINE_LOOP);
        glVertex2f(-100, 100);
        glVertex2f(-100, -100);
    glEnd();
    //Ponto 3
    glBegin(GL_LINE_LOOP);
        glVertex2f(-100, -100);
        glVertex2f(-60, -100);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(-30, -100);
        glVertex2f(100, -100);
    glEnd();
    // Ponto 4 - nao muda
    glBegin(GL_LINE_LOOP);
        glVertex2f(100, 100);
        glVertex2f(100, -100);
    glEnd();

    // Internos
    // Linha 1
    glBegin(GL_LINE_LOOP);
        glVertex2f(-100, -60);
        glVertex2f(-10, -60);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(10, -60);
        glVertex2f(100, -60);
    glEnd();
    // Linha 2
    glBegin(GL_LINE_LOOP);
        glVertex2f(-100, -20);
        glVertex2f(-50, -20);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(-20, -20);
        glVertex2f(100, -20);
    glEnd();
    // Linha 3
    glBegin(GL_LINE_LOOP);
        glVertex2f(-100, 20);
        glVertex2f(0, 20);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(20, 20);
        glVertex2f(100, 20);
    glEnd();
    // Linha 4
    glBegin(GL_LINE_LOOP);
        glVertex2f(-100, 60);
        glVertex2f(50, 60);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(70, 60);
        glVertex2f(100, 60);
    glEnd();
}

// Reinicia o jogo caso perca ou ganhe
void reiniciaJogo(void){
    x_1 = 0.0;
    x_2 = 12.0;
    y_1 = -120.0;
    y_2 = -108.0;
    if(vida == '0') resultado = 0;
    else resultado = 2;

    vida = '3';
}

// Seta valores caso haja colisao
void perdeVida(void)
{
    x_1 = 0.0;
    x_2 = 12.0;
    y_1 = -120.0;
    y_2 = -108.0;
    if(vida == '3') vida = '2';
    else if(vida == '2') vida ='1';
    else vida = '0';

    if(vida == '0') reiniciaJogo();

    glutSwapBuffers();
}

// Verifica se ha colisao
void colisao(void)
{
    if(x_1 < -100.0 || x_2 > 100.0) perdeVida();
    if((y_2 == -100.0 || y_1 == -100) && (x_1 < -60.0 || x_2 > -30.0))  perdeVida();        // Colisao Borda interna
    if((y_2 == -60.0 || y_1 == -60.0) && (x_1 < -10.0 || x_2 > 10.0)) perdeVida();          // Colisao Linha 1
    if((y_2 == -20.0 || y_1 == -20.0) && (x_1 < -50.0 || x_2 > -20.0))  perdeVida();        // Colisao Linha 2
    if((y_2 == 20.0 || y_1 == 20.0) && (x_1 < 0.0 || x_2 > 20.0)) perdeVida();              // Colisao Linha 3
    if((y_2 == 60.0 || y_1 == 60.0) && (x_1 < 50.0 || x_2 > 70.0))   perdeVida();           //Colisao Linha 4
    if((y_2 == 100.0 || y_1 == 100.0) && (x_1 < -20.0 || x_2 > 20.0))   perdeVida();        // Colisao Borda externa
    if((y_2 == 100.0 || y_1 == 100.0) && ((x_1 > -20.0 && x_1 < 20) || (x_2 < 20.0 && x_2 > -20.0))) reiniciaJogo();

    //glutPostRedisplay();
    glutSwapBuffers();
}

// Função que desenha esfera
void desenhaRetangulo(void)
{
//    vec3 points[sides * (sides-1)];
//    colisao();
    glBegin(GL_QUAD_STRIP);
        glColor3f(r_1,g_1,b_1);
        glVertex3f(x_1, y_1, 0);
        glVertex3f(x_1, y_2, 0);
        glVertex3f(x_2, y_1, 0);
        glVertex3f(x_2, y_2, 0);
    glEnd();

    glutSwapBuffers();
}

// Função callback chamada para fazer o desenho
void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    // Define a cor corrente
    glColor3f(r,g,b);

    DesenhaTexto("VIDAS: ", 90, 130);
    DesenhaTexto(&vida, 125, 130);
    if(!resultado){
        DesenhaTexto("* GAME OVER *", -20, 130);
        resultado = 1;
    }
    else if(resultado==2)   DesenhaTexto("VOCE VENCEU! PARABENS!", -35, 130);

    desenhaLinhas();
    desenhaRetangulo();
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    win=150.0f;
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(45,fAspect,0.5,500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	gluLookAt(0,60,150, 0,0,0, 0,1,0);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);
    view_w = w;
    view_h = h;
    fAspect = (GLfloat)w/(GLfloat)h;

    EspecificaParametrosVisualizacao();
    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (-win, win, -win, win);
}

// Gerenciamento do menu com as opções de cores
void MenuSobre(int op)
{
   switch(op) {
            case 0:
                     r = g = b = r_2 = 1.0f;
                     g_2 = b_2 - 0.0f;
                     glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                     break;
            case 1:
                     r = b = r_1 = b_1 = r_2 = b_2 = 0.0f;
                     g = g_1 = g_2 = 10.f;
                     glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                     break;
    }
    glutPostRedisplay();
}

// Gerenciamento do menu com as opções de cores
void MenuDados(int op)
{
   switch(op) {
            case 0:
                    if(r == 1.0f && g == 1.0f && b == 1.0f){
                        r_1 = 1.0f;
                        g_1 = 1.0f;
                        b_1 = 1.0f;
                    }
                    else{
                        r_1 = 0.0f;
                        g_1 = 0.0f;
                        b_1 = 0.0f;
                    }
                     break;
            case 1:
                     r_1 = 1.0f;
                     g_1 = 0.0f;
                     b_1 = 0.0f;
                     break;
            case 2:
                     r_1 = 1.0f;
                     g_1 = 0.7f;
                     b_1 = 0.8f;
                     break;
    }
    glutPostRedisplay();
}

// Gerenciamento do menu principal
void MenuPrincipal(int op)
{
}

// Criacao do Menu
void CriaMenu()
{
    int menu,submenu1,submenu2;


	submenu1 = glutCreateMenu(MenuSobre);
	glutAddMenuEntry("Modo Escuro",0);
	glutAddMenuEntry("Matrix",1);
	//glutAddMenuEntry("Variante Delta",2);

    submenu2 = glutCreateMenu(MenuDados);
	glutAddMenuEntry("Preto/Branco",0);
	glutAddMenuEntry("Vermelho",1);
	glutAddMenuEntry("Rosa",2);

    menu = glutCreateMenu(MenuPrincipal);
	glutAddSubMenu("Janela",submenu1);
    glutAddSubMenu("Jogador",submenu2);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON)
         if (state == GLUT_DOWN)
            CriaMenu();

    glutPostRedisplay();
}

// Gerencia entrada de teclas especiais
void TeclasEspeciais(int key, int x, int y)
{
    if(key == GLUT_KEY_UP) {
           y_1 = y_1 + 2.0;
           y_2 = y_2 + 2.0;
           colisao();
           desenhaRetangulo();
    }
    if(key == GLUT_KEY_DOWN) {
           y_1 = y_1 - 2.0;
           y_2 = y_2 - 2.0;
           colisao();
           desenhaRetangulo();
    }
    if(key == GLUT_KEY_LEFT){
            x_1 = x_1 - 2.0;
            x_2 = x_2 - 2.0;
            colisao();
            desenhaRetangulo();
    }
    if(key == GLUT_KEY_RIGHT){
            x_1 = x_1 + 2.0;
            x_2 = x_2 + 2.0;
            colisao();
            desenhaRetangulo();
    }

    glutPostRedisplay();
}

// Gerencia entradas do teclado
void GerenciaTeclado(unsigned char key, int x, int y)
{
    if(key == 27) {
           exit(1);
    }
    glutPostRedisplay();
}

// Programa Principal
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(720, 900);
    glutInitWindowPosition(10,10);
    glutCreateWindow("LABIRINTO");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutMouseFunc(GerenciaMouse);
    glutKeyboardFunc(GerenciaTeclado);
    glutSpecialFunc(TeclasEspeciais);
    Inicializa();
    glutMainLoop();
}
