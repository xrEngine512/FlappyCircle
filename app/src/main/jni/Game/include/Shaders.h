#pragma once

GLchar vShaderStr[] =
"attribute vec2 vPosition;    \n"
"uniform vec2 vOffset;\n"
"void main()                  \n"
"{                            \n"
"   gl_Position = vec4(vPosition + vOffset, 0.0, 1.0);  \n"
"}                            \n";

GLchar fShaderStr[] =
"precision mediump float;\n"
"uniform vec4 vColor;\n"
"void main()                                  \n"
"{                                            \n"
"  gl_FragColor = vColor;					  \n"
"}                                            \n";