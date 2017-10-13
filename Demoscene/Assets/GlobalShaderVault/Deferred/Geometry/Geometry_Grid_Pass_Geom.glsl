#version 330


layout (points) in;
in vec4 vs_position[];
in vec3 CellCol[];
in float CellHeight[];
layout (triangle_strip,max_vertices = 30) out;


out vec3 WorldPos0;                                                                 
out vec3 Color;   
out vec3 Normal0;


uniform mat4 gWVP;
uniform mat4 gView;
uniform mat4 gWorld;
uniform mat4 gProjection;      

//uniform mat4  gWorld, gWVP;
uniform float halfSize;


void main()
{       	


	vec4 viewPos = gView * gWorld * gl_in[0].gl_Position;
    //gl_Position    = gWVP * vec4(Position, 1.0);
	gl_Position = gProjection * viewPos;
    TexCoord0      = TexCoord;                  
    Normal0        = (gWorld * vec4(Normal, 0.0)).xyz;   
   //WorldPos0      = (gWorld * vec4(Position, 1.0)).xyz;

    //WorldPos0      = viewPos.xyz;

         //fColor = vColor[0];




		vec4 position =  gl_in[0].gl_Position;
		vec3 color = CellCol[0];
		float height = CellHeight[0];

		//float halfSize = 0.25;
        // +X direction is "North", -X direction is "South"
        // +Y direction is "Up",    -Y direction is "Down"
        // +Z direction is "East",  -Z direction is "West
        //        N/S   U/D   E/W
		//thats fucking stupid!  -X should be west and X east
		//and why not just write each as WUN to correspond with the vectors
		//new Shit
		vec4 EUS = vec4( halfSize,  height,  halfSize, 0.0);

		vec4 EUN = vec4( halfSize,  height,  -halfSize, 0.0);

		vec4 WUN = vec4( -halfSize,  height,  -halfSize, 0.0);

		vec4 WUS = vec4( -halfSize,  height,  halfSize, 0.0);


		vec4 EDS = vec4( halfSize,  0.0,  halfSize, 0.0);

		vec4 EDN = vec4( halfSize,  0.0,  -halfSize, 0.0);

		vec4 WDN = vec4( -halfSize,  0.0,  -halfSize, 0.0);

		vec4 WDS = vec4( -halfSize,  0.0,  halfSize, 0.0);


		//I could easily turn this into vertex normals seeings as we allready have the midpoint
		vec3 upNormal = (gWorld * (vec4(0.0,1.0, 0.0, 0.0))).xyz;

        // Create a cube centered on the given point.

		gl_Position = gWVP * (position + EUS);
        WorldPos0 = (gWorld * (position + EUS)).xyz;
		viewPos.xyz;
		//Color = vec3(0.0, 1.0, 0.0);
		//yes yes, should renamed one of these
		Color = color;
		Normal0 = upNormal;

        EmitVertex();

		gl_Position = gWVP * (position + EUN);
        WorldPos0 = (gWorld * (position + EUN)).xyz;
		//Color = vec3(0.0, 1.0, 0.0);
		Color = color;
		Normal0 = upNormal;
		EmitVertex();

		gl_Position = gWVP * (position + WUN);
        WorldPos0 = (gWorld * (position + WUN)).xyz;
		//Color = vec3(0.0, 1.0, 0.0);
		Color = color;
		Normal0 = upNormal;
        EmitVertex();

		//first triangle
		EndPrimitive();

		gl_Position = gWVP * (position + EUS);
        WorldPos0 = (gWorld * (position + EUS)).xyz;
		//Color = vec3(0.0, 1.0, 0.0);
		Color = color;
		Normal0 = upNormal;
        EmitVertex();

		gl_Position = gWVP * (position + WUN);
        WorldPos0 = (gWorld * (position + WUN)).xyz;
		//Color = vec3(0.0, 1.0, 0.0);
		Color = color;
		Normal0 = upNormal;
        EmitVertex();

		gl_Position = gWVP * (position + WUS);
        WorldPos0 = (gWorld * (position + WUS)).xyz;
		//Color = vec3(0.0, 1.0, 0.0);
		Color = color;
		Normal0 = upNormal;
		EmitVertex();




		//second
		EndPrimitive();
		//end of up face

		vec3 southNormal = (gWorld * (vec4(0.0,0.0, -1.0, 0.0))).xyz;

		gl_Position = gWVP * (position + EDS);
        WorldPos0 = (gWorld * (position + EDS)).xyz;
		//Color = vec3(1.0, 0.0, 0.0);
		Color = color;
		Normal0 = southNormal;
        EmitVertex();

		gl_Position = gWVP * (position + EUS);
        WorldPos0 = (gWorld * (position + EUS)).xyz;
		//Color = vec3(1.0, 0.0, 0.0);
		Color = color;
		Normal0 = southNormal;
        EmitVertex();

		
		gl_Position = gWVP * (position + WUS);
        WorldPos0 = (gWorld * (position + WUS)).xyz;
		//Color = vec3(1.0, 0.0, 0.0);
		Color = color;
		Normal0 = southNormal;
        EmitVertex();
		//third
		EndPrimitive();

		gl_Position = gWVP * (position + EDS);
        WorldPos0 = (gWorld * (position + EDS)).xyz;
		//Color = vec3(1.0, 0.0, 0.0);
		Color = color;
		Normal0 = southNormal;
		EmitVertex();

		gl_Position = gWVP * (position + WUS);
        WorldPos0 = (gWorld * (position + WUS)).xyz;
		//Color = vec3(1.0, 0.0, 0.0);
		Color = color;
		Normal0 = southNormal;
        EmitVertex();

		gl_Position = gWVP * (position + WDS);
        WorldPos0 = (gWorld * (position + WDS)).xyz;
		//Color = vec3(1.0, 0.0, 0.0);
		Color = color;
		Normal0 = southNormal;
        EmitVertex();



		//fourth triangle
		EndPrimitive();
		//End of south face
		
		vec3 westNormal = (gWorld * (vec4(-1.0,0.0, 0.0, 0.0))).xyz;


		gl_Position = gWVP * (position + WUN);
        WorldPos0 = (gWorld * (position + WUN)).xyz;
		//Color = vec3(0.0, 0.0, 1.0);
		Color = color;
		Normal0 = westNormal;
		EmitVertex();


		gl_Position = gWVP * (position + WDN);
        WorldPos0 = (gWorld * (position + WDN)).xyz;
		//Color = vec3(0.0, 0.0, 1.0);
		Color = color;
		Normal0 = westNormal;
        EmitVertex();

		gl_Position = gWVP * (position + WUS);
        WorldPos0 = (gWorld * (position + WUS)).xyz;
		//Color = vec3(0.0, 0.0, 1.0);
		Color = color;
		Normal0 = westNormal;
        EmitVertex();


		EndPrimitive();

		//fifth

		gl_Position = gWVP * (position + WDN);
        WorldPos0 = (gWorld * (position + WDN)).xyz;
		//Color = vec3(0.0, 0.0, 1.0);
		Color = color;
		Normal0 = westNormal;
        EmitVertex();
		

		gl_Position = gWVP * (position + WDS);
        WorldPos0 = (gWorld * (position + WDS)).xyz;
		//Color = vec3(0.0, 0.0, 1.0);
		Color = color;
		Normal0 = westNormal;
        EmitVertex();

		gl_Position = gWVP * (position + WUS);
        WorldPos0 = (gWorld * (position + WUS)).xyz;
		//Color = vec3(0.0, 0.0, 1.0);
		Color = color;
		Normal0 = westNormal;
        EmitVertex();
		//sixth
		EndPrimitive();

		//West Face done

		vec3 eastNormal = (gWorld * (vec4(1.0,0.0, 0.0, 0.0))).xyz;

		gl_Position = gWVP * (position + EUN);
        WorldPos0 = (gWorld * (position + EUN)).xyz;
		//Color = vec3(1.0, 0.0, 0.0);
		Color = color;
		Normal0 = eastNormal;
		EmitVertex();

		gl_Position = gWVP * (position + EUS);
        WorldPos0 = (gWorld * (position + EUS)).xyz;
		//Color = vec3(1.0, 0.0, 0.0);
		Color = color;
		Normal0 = eastNormal;
        EmitVertex();

		gl_Position = gWVP * (position + EDN);
        WorldPos0 = (gWorld * (position + EDN)).xyz;
		//Color = vec3(1.0, 0.0, 0.0);
		Color = color;
		Normal0 = eastNormal;
        EmitVertex();


		EndPrimitive();

		//seventh

		gl_Position = gWVP * (position + EDN);
        WorldPos0 = (gWorld * (position + EDN)).xyz;
		//Color = vec3(1.0, 0.0, 0.0);
		Color = color;
		Normal0 = eastNormal;
        EmitVertex();
		
		gl_Position = gWVP * (position + EUS);
        WorldPos0 = (gWorld * (position + EUS)).xyz;
		//Color = vec3(1.0, 0.0, 0.0);
		Color = color;
		Normal0 = eastNormal;
        EmitVertex();

		gl_Position = gWVP * (position + EDS);
        WorldPos0 = (gWorld * (position + EDS)).xyz;
		//Color = vec3(1.0, 0.0, 0.0);
		Color = color;
		Normal0 = eastNormal;
        EmitVertex();


		//eight
		EndPrimitive();

		//East Face done
  		vec3 northNormal = (gWorld * (vec4(0.0,0.0, 1.0, 0.0))).xyz;

		gl_Position = gWVP * (position + EDN);
        WorldPos0 = (gWorld * (position + EDN)).xyz;
		//Color = vec3(0.0, 0.0, 1.0);
		Color = color;
		Normal0 = northNormal;
		EmitVertex();

		gl_Position = gWVP * (position + WUN);
        WorldPos0 = (gWorld * (position + WUN)).xyz;
		//Color = vec3(0.0, 0.0, 1.0);
		Color = color;
		Normal0 = northNormal;
        EmitVertex();

		gl_Position = gWVP * (position + EUN);
        WorldPos0 = (gWorld * (position + EUN)).xyz;
		//Color = vec3(0.0, 0.0, 1.0);
		Color = color;
		Normal0 = northNormal;
        EmitVertex();




		EndPrimitive();

		//ninth
		gl_Position = gWVP * (position + EDN);
        WorldPos0 = (gWorld * (position + EDN)).xyz;
		//Color = vec3(0.0, 0.0, 1.0);
		Color = color;
		Normal0 = northNormal;
        EmitVertex();
		
		gl_Position = gWVP * (position + WDN);
        WorldPos0 = (gWorld * (position + WDN)).xyz;
		//Color = vec3(0.0, 0.0, 1.0);
		Color = color;
		Normal0 = northNormal;
        EmitVertex();

		gl_Position = gWVP * (position + WUN);
        WorldPos0 = (gWorld * (position + WUN)).xyz;
		//Color = vec3(0.0, 0.0, 1.0);
		Color = color;
		Normal0 = northNormal;
        EmitVertex();


		//LAST ONE fuck the bottom!
		EndPrimitive();
		//North face fucking done



    //TexCoord0      = TexCoord;                  

    //Normal0        = (gWorld * vec4(Normal, 0.0)).xyz;   

    //WorldPos0      = (gWorld * vec4(Position, 1.0)).xyz;


}
