#version 330                                                                        
                                                                                    
                                          
//layout (location = 0) in vec2 Position;
in vec2 Position;
//out vec4 WorldPos0;                                                                 


void main()
{       

   gl_Position =  vec4(Position.x,0.0,Position.y, 1.0);



}
