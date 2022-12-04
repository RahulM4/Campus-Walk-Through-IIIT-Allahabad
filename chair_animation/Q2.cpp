#include <GL/glut.h>
#include <math.h>
const double PI = 3.141592653589793238463;
float leg_width = 2;
float table_leg_height = 10;
float table_top_size = 15;
float platter_width = 4;
float platter_size = 10;
float circle_r = 2;
float chair_distance = 5;
float l = 7;
float alpha = atan(0.714f);
float angle = 0;
int refreshMills = 15;
float angular_velocity = 0.01f;
bool sequence1= false;
bool sequence2= false;
bool sequence3= false;
float table_v = -0.1f;
float table_bl[2] = {0,0};
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
void timer(int value) {
  glutPostRedisplay();      // Post re-paint request to activate display()
  glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}
void renderScene() {
  glClearColor(1.0f,1.0f,1.0f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho( -10, 50, -10, 50, -1, 1 );

  glMatrixMode( GL_MODELVIEW );
  glColor3f(0,0,0);
  glLoadIdentity();
  glRectf(-10,0,50,-1);
  if (sequence2) {
    glPushMatrix();
    glTranslatef(table_bl[0],0,0);
  }
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

  if (sequence2) {
    glPopMatrix();
  }
  //chair
  float table_bottom_right[2] = {table_top_size + leg_width, 0};
  float chair_bl[2] = {table_bottom_right[0] + chair_distance, 0};
  glColor3f(0,0,1);//blue
  glPushMatrix();
  glTranslatef(chair_bl[0],chair_bl[1],0);
  glRotatef(angle * 180 / 3.14, 0.0f, 0.0f, 1.0f);
  glTranslatef(-chair_bl[0],-chair_bl[1],0);
  glRectf(chair_bl[0],0,chair_bl[0] + leg_width,l);
  glRectf(chair_bl[0],l,chair_bl[0] + l,l + leg_width);
  glRectf(chair_bl[0] + l,0,chair_bl[0]  +l+leg_width,3*l);
  glPopMatrix();
  glFlush();
  if (!sequence1 || sequence3) {
    return;
  }
  angle += angular_velocity;

  if (angle > alpha) sequence2 = true;
  if (sequence2) table_bl[0] += table_v;
  if (angle > PI/3) sequence3 = true;
}
void keyboard(unsigned char key, int x, int y)
{
	//-------- spin --------
	if(key=='x')
	{
		sequence1 = true;
	}
	//-------- reset -------
}
int main(int argc, char*argv[]) {
  glutInit( &argc, argv );
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Rahul Mahto IIT2020022");
  glutDisplayFunc(renderScene);
  glutTimerFunc(0, timer, 0);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
