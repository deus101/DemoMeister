#version 330                                                                        
                                                                                    
                                          
layout(location = 0) in vec2 Position;
layout(location = 1) in vec3 Colour;
layout(location = 2) in float Height;
//in vec2 Position;
//out vec4 WorldPos0;                                                                 
out vec3 CellCol;
out float CellHeight;
void main()
{       

   gl_Position =  vec4(Position.x,0.0,Position.y, 1.0);
   CellCol = Colour;
   CellHeight = Height;


}
