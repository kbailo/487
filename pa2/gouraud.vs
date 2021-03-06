/*
 * Copyright (c) 2007, 2011, 2012 University of Michigan, Ann Arbor.
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
 * Authors: Sugih Jamin and Manoj Rajagopalan
 *
*/
#version 120

void 
main(void) 
{
  vec4 position = gl_ModelViewMatrix * gl_Vertex;
  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
//    gl_FrontMaterial, gl_LightModel, and gl_LightSource[]
    
//    gl_FrontColor.rgb = gl_Color.rgb * diffuse;
    
    
  /* TASK 7: YOUR CODE HERE
   *
   * You may want to consult the lecture notes on Gouraud shading.
   * According to the OpenGL2.1 spec, pp. 59-60:
   *
   * When viewer is not at infinity, OpenGL fixed-function fixes view
   * vector to (0.0, 0.0, 1.0).  Do this only for Gouraud, not for Phong.
   *
   * OpenGL also uses Blinn's half vector in computing specular
   * lighting.  So you need to compute and use the half vector.  Don't
   * use the halfVector of gl_LightSource, it doesn't seem to hold the
   * right value.  Also you should use material shininess as is, without
   * multiplying it by 4.0.
   *
   * Remember to take distance attenuation into account.  Also don't
   * forget to add BOTH global and local ambient to your lighting
   * computation.
   *
   * OpenGL adds contribution to the total color whenever
   * dot(n,l) != 0, not just when dot(n,l) < 0.
   */
  gl_FrontColor.a = 0.0;
}
