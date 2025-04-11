//Programa para rotacionar um triangulo em torno de seu baricentro usando as funções do OpenGL

#include <GL/glut.h>
#include <stdio.h>

// Coordenadas dos vértices do triângulo
GLfloat vertices[3][2] = {{-0.5, -0.5}, {0.5, -0.5}, {0.0, 0.5}}; // Ângulo de rotação
GLfloat angle = 0.0;

// Função para calcular o baricentro do triângulo
void calcularBaricentro(GLfloat *baricentro) {
    for (int i = 0; i < 2; i++) {
        baricentro[i] = 0.0;
    for (int j = 0; j < 3; j++) {
        baricentro[i] += vertices[j][i]; }
        baricentro[i] /= 3.0;
    }
}

// Função para desenhar o triângulo
void desenharTriangulo()
{ 
    glColor3f(1.0, 0.0, 0.0); // Cor vermelha
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++) {
        glVertex2fv(vertices[i]); }
    glEnd();
}

// Função de renderização
void display() { 
    glClear(GL_COLOR_BUFFER_BIT);
    // Calculando o baricentro 
    GLfloat baricentro[2]; 
    calcularBaricentro(baricentro);
    // Rotacionando em torno do baricentro
    glPushMatrix();
    glTranslatef(baricentro[0], baricentro[1], 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0); // Rotaciona em torno do eixo z
    glTranslatef(-baricentro[0], -baricentro[1], 0.0);
    // Desenhando o triângulo
    desenharTriangulo();
    glPopMatrix();
    glutSwapBuffers(); 
}

// Função para atualizar a animação
void animate(int value) {
    angle += 1.0; // Incrementa o ângulo de rotação
    glutPostRedisplay(); // Redesenha a cena
    glutTimerFunc(10, animate, 0); // Chama a função novamente após 10 milissegundos
}

// Função de inicialização
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); 
    glMatrixMode(GL_PROJECTION); 
    gluOrtho2D(-1.0, 1.0, -1.0,1.0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
    glutInitWindowSize(500, 500);
    glutCreateWindow("Triângulo Rotacionado em torno do Baricentro"); 
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, animate, 0); // Chama a função de animação imediatamente
    glutMainLoop();
    return 0;
}
