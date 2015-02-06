#include "shaders.h"




GLint ShaderObject;
GLint VertexShader;
GLint FragmentShader;



//GLint ShaderObject;
//GLint VertexShader;
//GLint FragmentShader;
//GLint GeometryShader;

Shader_Progs::Shader_Progs()
{




	cout << "FUCKINGS! : " << endl;


	//CompileProgram();



}


void Shader_Progs::CompileProgram()
{


	GLchar *vsString;
	const GLchar *vsStringPtr[1];
	GLint success;

	vsString = LoadShaderText("Shaders/vertex.glsl");

	VertexShader = gl::CreateShader(gl::VERTEX_SHADER);
	vsStringPtr[0] = vsString;



	gl::ShaderSource(VertexShader, 1, vsStringPtr, NULL);
	free(vsString);

	gl::CompileShader(VertexShader);

	gl::GetShaderiv(VertexShader, gl::COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[2048];
		gl::GetShaderInfoLog(VertexShader, 2048, NULL, infoLog);
		fprintf(stderr, "epic Vertex #%d ffffail!\n", VertexShader);
		fprintf(stderr, "%s\n", infoLog);
		Sleep(10000);
		exit(0);
	}



	/*
	GLchar *gsString;
	const GLchar *gsStringPtr[1];

	gsString = LoadShaderText("geometry.glsl");

	GeometryShader  = gl::CreateShader( gl::GL_GEOMETRY_SHADER );
	gsStringPtr[0] = gsString;

	gl::ShaderSource(GeometryShader, 1, gsStringPtr, NULL);
	free(gsString);


	gl::CompileShader(GeometryShader);
	gl::GetShaderiv(GeometryShader, gl::GL_COMPILE_STATUS, &success);
	if (!success)
	{
	GLchar infoLog[2048];
	gl::GetShaderInfoLog(GeometryShader, 2048, NULL, infoLog);
	fprintf(stderr, "epic #%d fail!\n", GeometryShader);
	fprintf(stderr, "%s\n", infoLog);
	Sleep(10000);
	exit(0);
	}

	*/
	//wonderfull world of fragments

	GLchar *fsString;
	const GLchar *fsStringPtr[1];

	fsString = LoadShaderText("Shaders/fragment.glsl");

	FragmentShader = gl::CreateShader(gl::FRAGMENT_SHADER);
	fsStringPtr[0] = fsString;


	gl::ShaderSource(FragmentShader, 1, fsStringPtr, NULL);
	free(fsString);

	gl::CompileShader(FragmentShader);
	gl::GetShaderiv(FragmentShader, gl::COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[2048];
		gl::GetShaderInfoLog(FragmentShader, 2048, NULL, infoLog);
		fprintf(stderr, "epic #%d fail!\n", FragmentShader);
		fprintf(stderr, "%s\n", infoLog);
		Sleep(10000);
		exit(0);
	}


	ShaderObject = gl::CreateProgram();

	cout << "VertexID! : " << VertexShader << endl;
	//	cout << "GeometryID!: "<< GeometryShader << endl;
	cout << "FragmentID! : " << FragmentShader << endl;

	gl::AttachShader(ShaderObject, VertexShader);

	//gl::AttachShader(ShaderObject, GeometryShader);

	gl::AttachShader(ShaderObject, FragmentShader);
	/*
	gl::ProgramParameteri(ShaderObject,gl::GL_GEOMETRY_INPUT_
	,gl::GL_TRIANGLES);
	gl::ProgramParameteri(ShaderObject,gl::GL_GEOMETRY_OUTPUT_TYPE,gl::GL_TRIANGLE_STRIP);
	int temp;

	gl::GetIntegerv(gl::GL_MAX_GEOMETRY_OUTPUT_VERTICES,&temp);
	gl::ProgramParameteri(ShaderObject,gl::GL_GEOMETRY_VERTICES_OUT,temp);
	*/
	//gl::BindFragDataLocation(ShaderObject, 0, "output");
	gl::LinkProgram(ShaderObject);



	gl::GetProgramiv(ShaderObject, gl::LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[2048];
		gl::GetProgramInfoLog(ShaderObject, 2048, NULL, infoLog);
		fprintf(stderr, "epic #%d fail!\n", VertexShader);
		//fprintf(stderr, "epic #%d fail!\n", GeometryShader);
		fprintf(stderr, "epic #%d fail!\n", FragmentShader);
		fprintf(stderr, "%s\n", infoLog);
		Sleep(10000);
		exit(0);
	}
	gl::ValidateProgram(ShaderObject);
	gl::GetProgramiv(ShaderObject, gl::VALIDATE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[2048];
		gl::GetProgramInfoLog(ShaderObject, 2048, NULL, infoLog);
		fprintf(stderr, "epic #%d fail!\n", VertexShader);
		//fprintf(stderr, "epic #%d fail!\n", GeometryShader);
		fprintf(stderr, "epic #%d fail!\n", FragmentShader);
		fprintf(stderr, "%s\n", infoLog);
		Sleep(10000);
		exit(0);
	}
	cout << "ShaderObject! : " << ShaderObject << endl;

	//POSLoc = gl::GetAttribLocation(ShaderObject,"vertexPosition_modelspace");
	//UVLoc = gl::GetAttribLocation(ShaderObject, "vertexUV"); 
	//NORMLoc = gl::GetAttribLocation(ShaderObject, "vertexNormal_modelspace"); 
	//gl::UseProgram(ShaderObject );

}

GLchar *Shader_Progs::LoadShaderText(const char *fileName)
{
	GLchar *shaderText = NULL;
	GLint shaderLength = 0;
	FILE *fp;

	fp = fopen(fileName, "r");
	if (fp != NULL)
	{
		while (fgetc(fp) != EOF)
		{
			shaderLength++;
		}
		rewind(fp);
		shaderText = (GLchar *)malloc(shaderLength + 1);
		if (shaderText != NULL)
		{
			fread(shaderText, 1, shaderLength, fp);
		}
		shaderText[shaderLength] = '\0';
		fclose(fp);
	}

	return shaderText;
}


void Shader_Progs::Sleep( unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
