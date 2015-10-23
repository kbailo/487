/*
 * Copyright (c) 2011 University of Michigan, Ann Arbor.
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
 * Author: Sugih Jamin
*/
#include "matmv.h"
#include <iostream>
using namespace std;

/*
 * YOUR goal here is to set up the current transformation matrix
 * ((*this)) with the appropriate matrix to perform the transformation
 * you want.
*/
MatModView CTM;  // current transformation matrix
    
void MatModView::
translate(float tx, float ty, float tz)
{
    
  /* YOUR CODE HERE */
    CTM(0,3) += tx;
    CTM(1,3) += ty;
    CTM(2,3) += tz;
    cout << CTM << endl;

  return;
}
  
void MatModView::
scale(float sx, float sy, float sz)
{
    XMat4f copy = CTM;
    XMat4f s;
    s(0,0) = sx;
    s(1,1) = sy;
    s(2,2) = sz;
    s(3,3) = 0;
    //CTM.Identity();
    CTM *= (s);// * copy);
    XVec4f col = copy.column(3);
    CTM.setCol(3, col);
    cout << CTM << endl;
  /* YOUR CODE HERE */

  return;
}

void MatModView::
Xshearby(float hxy, float hxz)
{
    XMat4f copy = CTM;
    XMat4f s;
    s(0, 1) = hxy;
    s(0, 2) = hxz;
    //CTM.Identity();
    CTM *= (s);// * copy);
  /* YOUR CODE HERE */
    cout << CTM << endl;

  return;
}

void MatModView::
Yshearby(float hyx, float hyz)
{
    XMat4f copy = CTM;
    XMat4f s;
    s(1, 0) = hyx;
    s(1, 2) = hyz;
    //CTM.Identity();
    CTM *= s; //* copy);
  /* YOUR CODE HERE */
    cout << CTM << endl;

  return;
}

void MatModView::
Zshearby(float hzx, float hzy)
{
    XMat4f copy = CTM;
    XMat4f s;
    s(2, 0) = hzx;
    s(2, 1) = hzy;
    //CTM.Identity();
    CTM *= (s);// * copy);
  /* YOUR CODE HERE */
    cout << CTM << endl;

  return;
}

void MatModView::
rotateX(float theta)
{
  /* YOUR CODE HERE */
    XMat4f copy = CTM;
    XMat4f s;
    s(1,1) = cos(theta);
    s(1,2) = -sin(theta);
    s(2,1) = sin(theta);
    s(2,2) =cos(theta);
    s(3,3) = 0;
    CTM.Identity();
    CTM *= (s * copy);
    XVec4f col = copy.column(3);
    CTM.setCol(3, col);
    cout << CTM << endl;
    
  return;
}

void MatModView::
rotateY(float theta)
{
  /* YOUR CODE HERE */
    XMat4f copy = CTM;
    XMat4f s;
    s(0,0) = cos(theta);
    s(0,2) = -sin(theta);
    s(2,0) = sin(theta);
    s(2,2) =cos(theta);
    s(3,3) = 0;
    CTM.Identity();
    CTM *= (s* copy);
    XVec4f col = copy.column(3);
    CTM.setCol(3, col);
    cout << CTM << endl;
  return;
}

void MatModView::
rotateZ(float theta)
{
  /* YOUR CODE HERE */
    XMat4f copy = CTM;
    XMat4f s;
    s(0,0) = cos(theta);
    s(0,1) = -sin(theta);
    s(1,0) = sin(theta);
    s(1,1) =cos(theta);
    s(3,3) = 0;
    //CTM.Identity();
    CTM *= (s);// * copy);
    XVec4f col = copy.column(3);
    CTM.setCol(3,col);
    cout << CTM << endl;
  return;
}
