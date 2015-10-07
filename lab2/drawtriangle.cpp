/*
 * Copyright (c) 2008, 2011, 2014 University of Michigan, Ann Arbor.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of Michigan, Ann Arbor. The name of the University 
 * may not be used to endorse or promote products derived from this 
 * software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Authors: Manoj Rajagopalan, Sugih Jamin
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
using namespace std;

/* Include the GL headers */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* Where was the mouse last clicked? */
#define NVERTICES 3
int vertex[NVERTICES][2]; /* Array of 2D points */

/* Flag to indicate the number of vertices that the user has set by clicking */
int vvalid=0;

/* screen width and height - screen refers to
   window within which we draw*/
#define DELTA 25
GLdouble screen_width=51*DELTA, screen_height=32*DELTA;

/* Handle to the GLUT window */
int wd;

void
drawpoint(GLint x, GLint y, GLclampf r, GLclampf g, GLclampf b)
{
  glColor3f(r,g,b);
  glRecti(x*DELTA, y*DELTA, (x+1)*DELTA, (y+1)*DELTA);
  /* NOTE: you cannot call glRect within a glBegin()...glEnd() block */
  
  return;
}


/* Display callback */
void
display(void)
{       
  int i;
        

  /* Set background to white */
  glClear(GL_COLOR_BUFFER_BIT);
        
  /* Draw a grey grid */
  glColor3f(0.5, 0.5, 0.5);
  glLineWidth(1.0);
  glBegin(GL_LINES);
  /* vertical lines */
  for (i=0; i<screen_width; i+=DELTA) {
    glVertex2i(i,0);
    glVertex2i(i,screen_height);
  }
  /* horizontal lines */
  for (i=0; i<screen_height; i+=DELTA) {
    glVertex2i(0,i);
    glVertex2i(screen_width, i);
  }
  glEnd();
        
  /* Draw the first point (square) in red, if valid) */
  if (vertex[0][0]>=0 && vertex[0][1]>=0)
    drawpoint(vertex[0][0], vertex[0][1], 1.0, 0.0, 0.0);
        
  /* Draw the second point (square) in green, if valid) */
  if (vertex[1][0]>=0 && vertex[1][1]>=0)
    drawpoint(vertex[1][0], vertex[1][1], 0.0, 1.0, 0.0);
        
  /* Draw the third point (square) in blue, if valid) */
  if (vertex[2][0]>=0 && vertex[2][1]>=0)
    drawpoint(vertex[2][0], vertex[2][1], 0.0, 0.0, 1.0);
        
  if (vvalid == 3) {
    /* Draw solid, black triangle between vertices */
    glLineWidth(3.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2i(vertex[0][0]*DELTA+DELTA/2, vertex[0][1]*DELTA+DELTA/2);
    glVertex2i(vertex[1][0]*DELTA+DELTA/2, vertex[1][1]*DELTA+DELTA/2);
    glVertex2i(vertex[2][0]*DELTA+DELTA/2, vertex[2][1]*DELTA+DELTA/2);
    glEnd();
                
    /* TODO - implement the triangle rasterization algorithm here.
       int vertex[0], vertex[1] and vertex[2] store integer coordinates 
       of the vertices.  The support code does the task of trapping mouse 
       clicks and setting these
       NOTE: Interpolate the color between the endpoints to get a 
       gradual transition
    */
    /* YOUR CODE HERE */
      int xmin, xmax, ymin, ymax, dx, dy;
      if (vertex[0][0] < vertex[1][0]){
          xmin = vertex[0][0];
          xmax = vertex[1][0];
      }
      else{
          xmax = vertex[0][0];
          xmin = vertex[1][0];
      }
      xmin = xmin < vertex[2][0] ? xmin : vertex[2][0];
      xmax = vertex[2][0] < xmax ? xmax : vertex[2][0];
      dx = xmax - xmin + 1;
      if (vertex[0][1] < vertex[1][1]){
          ymin = vertex[0][1];
          ymax = vertex[1][1];
      }
      else{
          ymax = vertex[0][1];
          ymin = vertex[1][1];
      }
      ymin = ymin < vertex[2][1] ? ymin : vertex[2][1];
      ymax = vertex[2][1] < ymax ? ymax : vertex[2][1];
      dy = ymax - ymin + 1;
    
      
//      A = (y1-y2)
//      B = (x2-x1)
//      C = -(x1*y2 - x2*y1)
//      Ax + By = C
      int x1, x2, y1, y2;
      double dr, dg, db;
      
      double grid[dx][dy][4];
      for (int i = 0; i < 3; ++i){
          switch (i) {
              case (0):
                  x1 = vertex[1][0];
                  y1 = vertex[1][1];
                  x2 = vertex[2][0];
                  y2 = vertex[2][1];
                  break;
              case (1):
                  x1 = vertex[0][0];
                  y1 = vertex[0][1];
                  x2 = vertex[2][0];
                  y2 = vertex[2][1];
                  break;
              default:
                  x1 = vertex[1][0];
                  y1 = vertex[1][1];
                  x2 = vertex[0][0];
                  y2 = vertex[0][1];
                  break;
          }
          int A = y1 - y2;
          int B = x2 - x1;
          int C = (x1*y2 - x2*y1);
          if (i == 0){
              dr = abs(A*vertex[0][0] + B*vertex[0][1] + C)/sqrt(A*A + B*B);
              cout << "dr = " << dr << endl;
          }
          else if ( i == 1){
              dg = abs(A*vertex[1][0] + B*vertex[1][1] + C)/sqrt(A*A + B*B);
              cout << "dg = " << dg << endl;
          }
          else{
              db = abs(A*vertex[2][0] + B*vertex[2][1] + C)/sqrt(A*A + B*B);
              cout << "db = " << db << endl;
          }
          
          
          C = -C;
          for (int x = 0; x < dx ; ++x) {
              for (int y = 0 ; y < dy; ++y){
                  if (grid[x][y][0] == 1 or !i){
                      if((A * (x+xmin) + B * (y+ymin) <= C) == (A * vertex[i][0] + B * vertex[i][1] <= C)
                         or (A * (x+xmin) + B * (y+ymin) >= C) == (A * vertex[i][0] + B * vertex[i][1] >= C)){
                          if (i == 2){
                              grid[x][y][3] = (abs(A*(x+xmin) + B*(y+ymin) - C)/sqrt(A*A + B*B));
                              drawpoint(x+xmin, y+ymin, grid[x][y][1]/dr, grid[x][y][2]/dg, grid[x][y][3]/db);
                          }
                          else if(i == 1){
                              grid[x][y][2] = (abs(A*(x+xmin) + B*(y+ymin) - C)/sqrt(A*A + B*B));
                          }
                          else{
                              grid[x][y][0] = 1;
                              grid[x][y][1] = (abs(A*(x+xmin) + B*(y+ymin) - C)/sqrt(A*A + B*B));
                          }
                          
                      }
                      else{
                          grid[x][y][0] = 0;
                      }
                  }
                  
              }
          }
          
      }
      
  }

  /* Force OpenGL to start drawing */
  glutSwapBuffers();
  
  return;
}

/* Mouse click event callback */
void
mouse(int button, int state, int x, int y)
{
  int i;

  /* Trap left-clicks */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    if (vvalid==0) {
      vertex[0][0] = x/DELTA;
      vertex[0][1] = (((int) screen_height)-y)/DELTA;
      ++vvalid;
    } else if (vvalid==1) {
      vertex[1][0] = x/DELTA;
      vertex[1][1] = (((int) screen_height)-y)/DELTA;
      ++vvalid;
    } else if (vvalid==2) {
      vertex[2][0] = x/DELTA;
      vertex[2][1] = (((int) screen_height)-y)/DELTA;
      ++vvalid;
    } else {
      for (i = 0; i < NVERTICES; i++) {
        vertex[i][0] = -1;
        vertex[i][1] = -1;
      }
      vvalid = 0;
    }
    glutPostRedisplay();
  }
  
  return;
}

/* Keyboard callback */
void
kbd(unsigned char key, int x, int y)
{
  int i;

  switch((char)key) {
                        
  case 'q':
    glutDestroyWindow(wd);
    exit(0);
    break;
                        
  case ' ':
  case 27:
    for (i = 0; i < NVERTICES; i++) {
      vertex[i][0] = -1;
      vertex[i][1] = -1;
    }
    vvalid = 0;
    glutPostRedisplay();
    break;
                        
  }
  
  return;
}

/* OpenGL resize callback */
void
reshape(int w, int h)
{
  /* Save new screen dimensions */
  screen_width = (GLdouble) w;
  screen_height = (GLdouble) h;
        
  /* Instruct Open GL to use the whole window for drawing */
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
        
  /* Do not perform projection transformations - later in the course */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
        
  /* Set coordinate system to first quadrant and bound x and y */
  glOrtho(0.0, screen_width, 0.0, screen_height, -1.f, 1.f);
  
  return;
}

int
main(int argc, char *argv[])
{
  int i;

  /* Initialize GLUT, let it extract command-line GLUT options that
     you may provide 
     - NOTE THE & BEFORE argc
  */
  glutInit(&argc, argv);
        
  /* Want single window and color will be specified as RGBA values */
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
        
  /* Set initial window size
     screen_width and screen_height have been above
  */
  glutInitWindowSize((int)screen_width, (int)screen_height);
        
  /* Create the window and store the handle to it */
  wd = glutCreateWindow("Lab2: Triangle Rasterization" /* title */ );
        
  /* --- register callbacks for GUI events --- */
  /* Register function that paints the window
     - Calling OpenGL functions or otherwise
  */
  glutDisplayFunc(display);
        
  /* Register function to handle window reshapes */
  glutReshapeFunc(reshape);
        
  /* Register keyboard event processing function */
  glutKeyboardFunc(kbd);
        
  /* Register mouse-click event callback */
  glutMouseFunc(mouse);
        
  /* -- init data -- */
  for (i = 0; i < NVERTICES; i++) {
    vertex[i][0] = -1;
    vertex[i][1] = -1;
  }
  vvalid = 0;
        
  /* -- init GL -- */
  glClearColor(1.0, 1.0, 1.0, 1.0);
  /* Fill the 'front' face of polygons - rectangles in our case */
  glPolygonMode(GL_FRONT, GL_FILL); 

  /* Start the GLUT event loop */
  glutMainLoop();
        
  exit(0);
}
