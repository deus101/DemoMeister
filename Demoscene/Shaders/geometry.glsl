#version 120 
#extension GL_EXT_geometry_shader4 : enable

varying vec3 vertex_light_position;
varying vec3 vertex_light_half_vector;
varying vec3 vertex_normal;
varying vec4 HemiDif;

void main(void)
{	
	
	
		//increment variable
		int i;

		//Pass-thru!
		for(i=0; i< gl_VerticesIn; i++){
			gl_Position = gl_PositionIn[i];
			EmitVertex();
		}
		EndPrimitive();		
		
	for(i=0; i< gl_VerticesIn; i++){
		gl_Position = gl_PositionIn[i];
		gl_Position = gl_Position + vec4( 5.0, -10.0, 0.0, 0.0);
		EmitVertex();
	}
	EndPrimitive();		
	
	for(i=0; i< gl_VerticesIn; i++){
		gl_Position = gl_PositionIn[i];
		gl_Position = gl_Position + vec4( 5.0, 10.0, 1.0, 0.0);
		EmitVertex();
	}
	EndPrimitive();																				
		
}
