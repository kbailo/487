/*
 * Copyright (c) 2007, 2011 University of Michigan, Ann Arbor.
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
 * Authors: Manoj Rajagopalan, Ari Grant, Sugih Jamin
 *
*/
#include <cassert>
#include <iostream>
using namespace std;

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "scene.h"

int wd;
int screen_w = 640;
int screen_h = 400;

XVec3f eye_pos(0,0,900);
Sphere reflecting_sphere(-100,-80,-100,75);

XVec3f Xaxis(1.0,0.0,0.0);
XVec3f Yaxis(0.0,1.0,0.0);
XVec3f Zaxis(0.0,0.0,1.0);

Colorf White(1.0,1.0,1.0);
Colorf Black(0.0,0.0,0.0);

Colorf 
raytrace(Ray const& ray, bool secondary)
{
  double t;
  
  // one diffuse light for the scene
  static Light const light0(XVec3f(-300.0,200.0,900.0),   // location
                            Black,       // ambient
                            .45*White,   // diffuse
                            Black,       // specular
                            1, 1.0e-3, 1.0e-4); // attenuation
        
    // front and back walls: respond to diffuse lighting only, mostly red
  static Material const fb_mat(Black, Colorf(1.0f, 0.1f, 0.1f), Black);
  // left and right walls: respond to diffuse lighting only, mostly green
  static Material const lr_mat(Black, Colorf(0.3f, 1.0f, 0.3f), Black);
  // top and bottom walls: respond to diffuse lighting only, mostly blue
  static Material const tb_mat(Black, Colorf(0.3f,0.3f, 1.0f), Black);

  static Plane const walls[] = { 
    Plane(-Zaxis, XVec3f(0,0,1000), fb_mat),   // back wall
    Plane( Zaxis, XVec3f(0,0,-3000), fb_mat),  // front wall
    Plane( Xaxis, XVec3f(-700,0,0), lr_mat),   // left wall
    Plane(-Xaxis, XVec3f(700,0,0),  lr_mat),   // right wall
    Plane( Yaxis, XVec3f(0,-600,0), tb_mat),   // floor
    Plane(-Yaxis, XVec3f(0,600,0),  tb_mat) }; // ceiling
        
  if (secondary || !reflecting_sphere.is_intersecting(ray)) {
                
    /* YOUR CODE HERE
     *          
     * If this is a secondary ray (we've already touched the sphere)
     * or the ray doesn't intersect the sphere then find out which wall
     * the ray is intersecting and obtain its color. To do this,
     * (1) call Plane::intersect(ray) for each of the walls so that you 
     *     get the t parameter for the ray at which the intersection occurs. 
     *     Negative t tells you that the plane is behind the origin of the 
     *     ray (the eye). Also, t is an indicator of how far one must travel 
     *     along the ray to reach the point of intersection.
     * (2) Once you get the 't', computing the actual world point can be done
     *     by calling Ray::pt(t). See scene.h
     * (3) Only the 't' that is within the visible world is useful for
     *     rendering.  Keep track of the wall corresponding to the visible
     *     't' also.
     * (4) Calculate the color at the intersection point of the ray and the 
     *     wall by calling Light::pt(Pt, plane-normal, plane-material). 
     *     See scene.h
     * (5) Hard shadow: If the ray from light source to point on the wall 
     *     intersects the sphere, then the sphere casts a shadow. Otherwise 
     *     the wall reflects light in the usual way. You may want to 
     *     implement the case where the ray intersects the sphere first 
     *     and then come back here to implement this last task.
    */
      double t;
      for (int i = 0; i < 6; ++i){
          t = walls[i].intersect(ray);
          if (t >= 0 and t < HUGE_VAL){
              XVec3f wp = ray.pt(t);
              if(wp(0) < 700.1 and wp(0) > -700.1 and wp(2) < 1000.1 and wp(2) > -3000.1
                 and wp(1) < 600.1 and wp(1) > -600.1){
                  Colorf color;
                  Ray r = Ray(light0.o, wp - light0.o);
                  if(reflecting_sphere.is_intersecting(r)){
                      color = Colorf(0.0, 0.0, 0.0);
                  }
                  else
                      color = light0.pt(wp, walls[i].n, walls[i].mat);
                  return color;
              }
          }
      }
  } else {
                
    /* YOUR CODE HERE
     * ray intersects sphere:
     * (1) Determine the point of intersection. Use Sphere::intersect(ray)
     * (2) Determine reflection vector.
     * (3) Create the reflected ray with this point and direction.
     * (4) recurse this function setting the "secondary" flag to true.
    */
      double t = reflecting_sphere.intersect(ray);
      XVec3f poi = ray.pt(t);
      XVec3f n = reflecting_sphere.unit_normal(poi);
      XVec3f r = ray.d - 2.0 * ((ray.d).dot(n) * n);
      Ray reflected_ray = Ray(poi, r);
      return raytrace(reflected_ray,true);
  }
  // YOUR CODE HERE: Remove this line after implementing the above
//  return Colorf(0.0f, 1.0f, 1.0f);
}

void 
display(void)
{
  int i, j;
  int screen_center_x = screen_w/2;
  int screen_center_y = screen_h/2;
 
  glBegin(GL_POINTS);
  for (i = 0; i < screen_w; i++) {
    for (j = 0; j < screen_h; j++) {
                        
      // Create a ray through the screen point
      XVec3f const s(double(i-screen_center_x), double(j-screen_center_y), 0.0);
      XVec3f const d(s - eye_pos);
      Ray const ray(eye_pos, d);
                        
      // trace the ray and get the color
      Colorf c = raytrace(ray, false);
                        
      // set this color
      glColor3f(c.red(), c.green(), c.blue());
      glVertex2f((GLfloat)i, (GLfloat)j);
    }
  }
  glEnd();
  glFlush();

  return;
}

void 
reshape(int w, int h)
{
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT);
  screen_w = w;
  screen_h = h;
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  gluOrtho2D(0,(GLdouble)w, 0, (GLdouble)h);

  return;
}

/* Keyboard callback */
void
kbd(unsigned char key, int x, int y)
{
  switch((char)key) {                 
  case 'h':
  case 'x':
    reflecting_sphere.c.x() -= 10.0;
    break;
                        
  case 'l':
  case 'X':
    reflecting_sphere.c.x() += 10.0;
    break;
                        
  case 'j':
  case 'y':
    reflecting_sphere.c.y() -= 10.0;
    break;
                        
  case 'k':
  case 'Y':
    reflecting_sphere.c.y() += 10.0;
    break;
                        
  case 'w':
  case 'z':
    reflecting_sphere.c.z() -= 10.0;
    break;
                        
  case 's':
  case 'Z':
    reflecting_sphere.c.z() += 10.0;
    break;
                        
  case 'q':
  case 27:
    glutDestroyWindow(wd);
    exit(0);
    break;

  default:
    break;
  }
    
  glutPostRedisplay();

  return;
}

int 
main(int argc, char *argv[])
{
  // glut functions to create the window and viewport
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(screen_w, screen_h);
  wd = glutCreateWindow("Lab6: Ray Tracing");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(kbd);

  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT);

  glutMainLoop();

  return(0);
}
