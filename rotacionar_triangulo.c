//Programa para rotacionar um triangulo em torno de seu baricentro sem usar as funções do OpenGL

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

// Ângulo de rotação
GLfloat angle = 0.0;
// Coordenadas dos vértices do triângulo
GLfloat vertices[3][2] = {{-0.5, -0.5}, {0.5, -0.5}, {0.0, 0.5}};

// Função para calcular o baricentro do triângulo
void calcularBaricentro(GLfloat *baricentro)
{
     for (int i = 0; i < 2; i++) {
        baricentro[i] = 0.0;
        for (int j = 0; j < 3; j++) {
            baricentro[i] += vertices[j][i]; }
        baricentro[i] /= 3.0;
    }
}

// Função para realizar a translação
void transladar(GLfloat x, GLfloat y)
{ 
    for (int i = 0; i < 3; i++) {
        vertices[i][0] += x;
        vertices[i][1] += y;
    } 
}

// Função para realizar a rotação
void rotacionar(GLfloat angulo){
    GLfloat baricentro[2]; 
    calcularBaricentro(baricentro);
    GLfloat cos_angulo = cos(angulo * 3.1429 / 180); 
    GLfloat sin_angulo = sin(angulo * 3.1429 / 180); 
    for (int i = 0; i < 3; i++) {
        // a formula de rotacao em relacao à origem
        // x' = xcosO - ysinO
        // y' = xsinO + ycosO 
        GLfloat x = vertices[i][0] - baricentro[0]; // fazemos a origem ser o bariecentro, logo subtraimos todas coordenadas pelo baricentro
        GLfloat y = vertices[i][1] - baricentro[1];
        vertices[i][0] = x * cos_angulo - y * sin_angulo + baricentro[0]; // somamos o baricentro de volta
        vertices[i][1] = x * sin_angulo + y * cos_angulo + baricentro[1]; 
    }
}

// Função para desenhar o triângulo
void desenharTriangulo()
{ 
    glColor3f(1.0, 0.0, 0.0); // Cor vermelha
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++) {
        glVertex2fv(vertices[i]);
    }
    glEnd();
}

// Função de renderização
void display() { 
    glClear(GL_COLOR_BUFFER_BIT);
    // Transladando para o centro da tela
    transladar(0.0, 0.0);
    // Rotacionando em torno do baricentro
    rotacionar(45.0);
    // Desenhando o triângulo
    desenharTriangulo();
    glutSwapBuffers();
}

// Função para atualizar a animação
void animate(int value) {
    angle += 0.2; // Incrementa o ângulo de rotação
    glutPostRedisplay(); // Redesenha a cena
    glutTimerFunc(50, animate, 0); // Chama a função novamente após 10 milissegundos
}

// Função de inicialização 
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Triângulo Rotacionado em torno do Baricentro (Manual)"); init();
    glutDisplayFunc(display);
    glutTimerFunc(0, animate, 0); // Chama a função de animação imediatamente
    glutMainLoop();
    return 0;
}