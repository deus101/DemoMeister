#version 330                                                                        
                                                                                    
in vec2 Position;                                             

uniform mat4 gWVP;

out gl_Position;
void main()
{       
    gl_Position    = gWVP * vec4(Position.X,0.0,Position.Y, 1.0);
            

}