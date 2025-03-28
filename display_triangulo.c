#include <GL/glut.h>

// Coordenadas dos vértices do triângulo
GLfloat vertices[3][2] = {{-0.5, -0.5}, {0.5, -0.5}, {0.0, 0.5}};

// Função para desenhar o triângulo
void desenharTriangulo() { 
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
    desenharTriangulo(); // Desenha o triângulo
    glutSwapBuffers(); 
}

// Função de inicialização
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Fundo branco
    glMatrixMode(GL_PROJECTION); 
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Define a área de visualização
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
    glutInitWindowSize(500, 500);
    glutCreateWindow("Triângulo Estático"); 
    init();
    glutDisplayFunc(display); // Registra a função de renderização
    glutMainLoop(); // Inicia o loop principal
    return 0;
}