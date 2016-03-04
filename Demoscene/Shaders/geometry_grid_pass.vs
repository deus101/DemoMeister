#version 330                                                                        
                                                                                    
in vec2 Position;                                             

uniform mat4 gWVP;

out vec4 gl_Position;
void main()
{       
    gl_Position    = gWVP * vec4(Position.x,0.0,Position.y, 1.0);
            

}