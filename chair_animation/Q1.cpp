#include <GL/glut.h>
#include <math.h>
float leg_width = 2;
float table_leg_height = 10;
float table_top_size = 15;
float platter_width = 4;
float platter_size = 10;
float circle_r = 2;
float chair_distance = 5;
float l = 7;

static void drawDisc(float cx, float cy,float radius) {
  glBegin(GL_POLYGON);
  double PI = 3.14;
  for (int i = 0; i <= 360; i++) {
    double angle = 2 * PI * i / 360;
    double x = cos(angle) * radius;
    double y = sin(angle) * radius;
    glVertex2d(cx + x, cy + y);
  }
  glEnd();
}
void renderScene() {
  glClearColor(1.0f,1.0f,1.0f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho( -10, 50, -10, 50, -1, 1 );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
//table
  glColor3f(0.5f, 0.35f, 0.05f);//brown munde
  glRectf(0,0,leg_width,table_leg_height);
  glRectf(0,table_leg_height,table_top_size,table_leg_height + leg_width);
  glRectf(table_top_size,table_leg_height +leg_width, table_top_size + leg_width, 0);
  float table_center[2] = {table_top_size /2, table_leg_height + leg_width};


//balls
  float platter_center[2] = {table_center[0],table_center[1] + platter_width};
  glColor3f(0.8f, 0.47f, 34/255);// ochre
  drawDisc(platter_center[0] - circle_r/2, platter_center[1] + circle_r/2, circle_r);
  glColor3f(1,0,0);// red
  drawDisc(platter_center[0] + circle_r/2, platter_center[1] + circle_r/2, circle_r);
  //platter
  glColor3f(0, 1, 0);//green
  glRectf(table_center[0] -  (platter_size/2),table_center[1],table_center[0] +  (platter_size/2),table_center[1] + platter_width);
  //chair
  float table_bottom_right[2] = {table_top_size + leg_width, 0};
  float chair_br[2] = {table_bottom_right[0] + chair_distance, 0};
  glColor3f(0,0,1);//blue
  glRectf(chair_br[0],0,chair_br[0] + leg_width,l);
  glRectf(chair_br[0],l,chair_br[0] + l,l + leg_width);
glRectf(chair_br[0] + l,0,chair_br[0]  +l+leg_width,3*l);
  glFlush();
}

int main(int argc, char*argv[]) {
  glutInit( &argc, argv );
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Rahul Mahto IIT2020022");
  glutDisplayFunc(renderScene);
  glutMainLoop();
  return 0;
}
