
#include "world.h"
//#include "vsGLInfoLib.h"
#define DegToRad 0.01745329f

GLfloat turn = 0.0;
GLuint VertexArrayID;
Shader_Progs o_progs;
//GLFrame camera;
composite stuff;
HSTREAM stream;
//diffuse light  
GLfloat dlr = 1.0;
GLfloat dlg = 1.0;
GLfloat dlb = 1.0;

//ambient light 
GLfloat alr = 0.5;
GLfloat alg = 0.5;
GLfloat alb = 0.5;

//specular light 
GLfloat slr = 1.0;
GLfloat slg = 1.0;
GLfloat slb = 1.0;

//light position variables
GLfloat lx = 1.0;
GLfloat ly = 6.0;
GLfloat lz = 0.0;

GLfloat lw = 0.0;

//For custom hemispherical lighting
GLfloat LightSource[] = { -20.0f, 20.0f, 0.0 };
GLfloat SkyC[] = { (73.0f / 255), (151.0f / 255), (208.0f / 255), 0.5f };
//GLfloat SkyC [] = { (1.0) , ( 1.0), (1.0), 1.0 };
GLfloat GroundC[] = { 0.9f, 0.9f, 0.9f, 1.0f };

GLfloat DiffuseLight[] = { dlr, dlg, dlb };
GLfloat AmbientLight[] = { alr, alg, alb };
GLfloat SpecularLight[] = { slr, slg, slb };

GLfloat LightPosition[] = { lx, ly, lz };
//GLfloat LightPosition[] = {lx, ly, lz, lw};
//VEC3 LightPosition(lx, ly, lz);


M3DVector3f LightObserver;
M3DVector3f ColorS;
M3DVector3f ColorG;
M3DMatrix44f matvec;




world::world()
{


	WindowID = 0;
	/*
	camera.SetOrigin(0.0, 0.0, 0.0);
	camera.SetForwardVector(0.0, 0.0, 1.0);
	camera.SetUpVector(0.0, 1.0, 0.0);
	camera.MoveUp(2.0f);
	camera.RotateLocalY(180.0f * DegToRad );
	camera.MoveForward(-30.0f);
	*/

	//define the modelview matrix here


	//camera.RotateLocalZ( -15.0f * DegToRad );
	stuff = composite();

	//Shader_Progs o_progs = Shader_Progs();


	//001 is ball 002 is the pyramid slope


	//stuff.AddActor(001, -1.0f, 1.0f, 1.0f);
	//stuff.AddActor(001, -1.0f, 1.0f, -1.0f);
	//stuff.AddActor(001, 1.0f, 1.0f, -1.0f);
	//stuff.AddActor(001, 1.0f, 1.0f, 1.0f);
	//stuff.AddActor(002,  0.0f, 0.5f, 0.0f);

	//this function can also be overloaded to recive new obj files

	//Perfect for collision responce

	//stuff.AddActor("cube.obj", -0.6f, 0.3f, -1.0f);

	//stuff.AddActor("cor.obj",0.0f, -1.9f, 6.0f);	
	//stuff.AddActor("cornor.obj",0.0f, -1.9f, -2.5f);
	//stuff.AddActor("cor.obj",0.0f, -1.9f, -11.0f);


	//stuff.AddActor(VEC3(0.7f, 0.7f, 0.7f), "p38.obj", "p38.mtl", 0.0f, 2.0f, 0.0f);
	//stuff.AddActor(VEC3(0.7f, 0.7f, 0.7f), "corridor.obj", "corridor.mtl", 0.0f, 0.0f, 0.0f);






	stuff.StartTimer();

}



void world::DrawStage()
{


	/*
	GLfloat fExtent = 20.0f;
	GLfloat fStep = 1.0f;
	GLfloat y = -2.0f;
	GLfloat fColor;

	GLfloat iStrip, iRun;

	GLint iBounce = 0;


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for(iStrip = -fExtent; iStrip <= fExtent; iStrip += fStep)
	{
	glShadeModel(GL_SMOOTH);
	//glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 1.0f, 0.0f);
	for(iRun = fExtent; iRun >= -fExtent; iRun -= fStep)
	{
	if((iBounce %2) == 0)
	fColor = 0.0f;
	else
	fColor = 0.5f;

	GLfloat mShininess[] = {50};

	GLfloat DiffuseMaterial[] = {fColor, fColor, fColor};
	GLfloat AmbientMaterial[] = {0.0, 0.0, 0.0};
	GLfloat SpecularMaterial[] = {fColor, fColor, fColor};

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DiffuseMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AmbientMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SpecularMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);



	glVertex3f(iStrip, y, iRun);
	glVertex3f(iStrip + fStep, y, iRun);

	iBounce++;
	}

	glEnd();
	}
	glDisable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	*/


}




void world::Water()
{
	/*
	srand((unsigned)time(NULL));
	GLfloat fExtent = 40.0f;
	GLfloat fStep = 0.5f;
	GLfloat Y = -2.0f;


	GLfloat iStrip, iRun;

	GLint iBounce = 0;

	GLfloat mShininess[] = {5};
	GLfloat DiffuseMaterial[] = {0.0, 0.0, 1.0};
	GLfloat AmbientMaterial[] = {0.2, 0.2, 0.2};
	GLfloat SpecularMaterial[] = {0.2, 0.2, 0.2};


	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DiffuseMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AmbientMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SpecularMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);

	glShadeModel(GL_FLAT);
	//glEnable(GL_COLOR_MATERIAL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for(iStrip = -fExtent; iStrip <= fExtent; iStrip += fStep)
	{
	glBegin(GL_TRIANGLE_STRIP);

	for(iRun = fExtent; iRun >= -fExtent; iRun -= fStep)
	{

	GLfloat random = GLfloat( (double(rand())/RAND_MAX)*0.5 );

	//glColor4f(0.0f, 0.0f, GLfloat((double(rand())/RAND_MAX)*1), 0.5f);
	//glVertex3f(iStrip, GLfloat((double(rand())/RAND_MAX)*0.2) + Y, iRun);
	//glVertex3f(iStrip + fStep, GLfloat((double(rand())/RAND_MAX)*0.2) + Y, iRun);
	//glColor4f(0.8f, 0.8f, 1.0f, 0.5f);
	glNormal3f(random, 1.0, random);
	glVertex3f(iStrip,  Y, iRun);
	glVertex3f(iStrip + fStep,  Y, iRun);

	iBounce++;
	}

	glEnd();
	}
	//glDisable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	*/

}

void world::HyperSpace()
{



}

void world::HyperPlane()
{
	/*

	GLfloat Y = -2.0f;
	GLfloat mShininess[] = {5};

	GLfloat DiffuseMaterial[] = {0.7, 0.0, 0.0};
	GLfloat AmbientMaterial[] = {0.2, 0.2, 0.2};
	GLfloat SpecularMaterial[] = {1.0, 1.0, 1.0};


	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DiffuseMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AmbientMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SpecularMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);


	glShadeModel(GL_FLAT);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-50.0f, Y, -50.0f);
	glVertex3f(-50.0f, Y, 50.0f);
	glVertex3f(50.0f, Y, 50.0f);
	glVertex3f(50.0f, Y, -50.0f);

	glEnd();

	glShadeModel(GL_SMOOTH);
	*/
}







void world::HyperHex()
{



	GLfloat S;
	GLfloat h;








}


void world::AfterInit()
{
	cout << "JUST THIS ONCE " << endl;
	gl::ClearColor(0.0f, 0.0f, 0.7f, 0.0f);

	gl::Enable(gl::DEPTH_TEST);
	gl::DepthFunc(gl::LESS);

	o_progs.CompileProgram();


	//stuff.AddActor(001, 0.0f, 5.0f, 15.0f);
	//stuff.AddActor(VEC3(0.7f, 0.7f, 0.7f), "Mesh/buddha.obj", "Mesh/buddha.mtl", 0.0f, 0.0f, 0.0f);
	stuff.AddActor(001, 0.0f, 5.0f, 15.0f);
	stuff.AddActor(VEC3(0.7f, 0.7f, 0.7f), "Mesh/p38.obj", "Mesh/p38.mtl", 0.0f, 0.0f, 0.0f);
	stuff.AddActor(VEC3(0.7f, 0.7f, 0.7f), "Mesh/hex.obj", "Mesh/hex.mtl", 0.0f, 10.0f, 0.0f);
	
	
	//stuff.AddActor(001, 0.0f, 5.0f, 15.0f);
	//stuff.AddActor(VEC3(0.7f, 0.7f, 0.7f), "corridor.obj", "corridor.mtl", 0.0f, 0.0f, 4.0f);
	//stuff.AddActor(VEC3(0.7f, 0.7f, 0.7f), "corridor.obj", "corridor.mtl", 0.0f, 0.0f, -10.0f);
	//stuff.AddActor(VEC3(0.7f, 0.7f, 0.7f), "corridor.obj", "corridor.mtl", 0.0f, 0.0f, 6.0f);
	//stuff.AddActor(VEC3(0.7f, 0.7f, 0.7f), "corridor.obj", "corridor.mtl", 0.0f, 0.0f, 9.0f);
	//stuff.AddActor(VEC3(0.7f, 0.7f, 0.7f), "p38.obj", "p38.mtl", -4.0f, 3.0f, 2.0f);
	//stuff.AddActor(VEC3(0.7f, 0.7f, 0.7f), "bench.obj", "bench.mtl", -4.0f, 3.0f, 2.0f);
	//stuff.AddActor(VEC3(0.7f, 0.7f, 0.7f), "cube_texture.obj", "cube_texture.mtl",0.0f, 2.0f,0.0f);
	//stuff.AddActor(VEC3(0.7f, 0.7f, 0.7f), "cube_texture.obj", "cube_texture.mtl", 0.0f, 0.0f, -2.0f);
	//stuff.AddActor(VEC3(0.7f, 0.7f, 0.7f), "cube_texture.obj", "cube_texture.mtl", 2.0f, 0.0f, 0.0f);
	//stuff.AddActor(VEC3(0.7f, 0.7f, 0.7f), "cube_texture.obj", "cube_texture.mtl", -4.0f, -4.0f,-1.0f);
	//stuff.AddActor(VEC3(0.7f, 0.7f, 0.7f), "cube_texture2.obj", "cube_texture2.mtl", 0.0f, 0.5f, 4.0f);
	//stuff.AddActor(VEC3(0.7f, 0.7f, 0.7f), "ground.obj", "ground.mtl", 0.0f, -2.0f, 0.0f); 
	//stuff.AddActor(VEC3(0.7f, 0.7f, 0.7f), "ground.obj", "ground.mtl", 0.0f, -0.5f, -5.5f); 
	//stuff.AddActor(VEC3(0.7f, 0.7f, 0.7f), "cube_texture.obj", "cube_texture.mtl", 0.0f, 0.0f, 0.0f);
	//stuff.AddActor(VEC3(0.7f, 0.7f, 0.7f), "p38.obj", "p38.mtl", -1.0f, -0.5f, -0.5f);
	//stuff.AddActor(002, 1.0f, 1.0f, -2.0f);
	//o_progs.CompileProgram();









	if (!BASS_Init(-1, 44100, 0, 0, 0))
		cout << "failed to init bass" << endl;
	stream = BASS_StreamCreateFile(false, "bf.ogg", 0, 0,
		BASS_STREAM_PRESCAN);
	if (!stream)
		cout << "failed to open tune" << endl;

	// rocket = sync_create_device("sync");



	//if (!(::rocket))
	//	cout << "out of memory?" << endl;

#ifndef SYNC_PLAYER
	//if (sync_connect(::rocket, "localhost", SYNC_DEFAULT_PORT))
	//	cout << "failed to connect to host" << endl;
#endif

	stuff.SortTracks();
	/* get tracks */
	//clear_r = sync_get_track(rocket, "clar.r");
	//clear_g = sync_get_track(rocket, "clear.g");
	//clear_b = sync_get_track(rocket, "clear.b");
	//cam_rot = sync_get_track(rocket, "cam.rot"),
	//cam_dist = sync_get_track(rocket, "cam.dist");

	/* let's roll! */
	BASS_Start();
	BASS_ChannelPlay(stream, false);












}
void world::InitLights()
{

	//ubo?
	//GLfloat DiffuseLight[] = {dlr, dlg, dlb}; 
	//GLfloat AmbientLight[] = {alr, alg, alb};
	//GLfloat SpecularLight[] = {slr, slg, slb};

	//GLfloat LightPosition[] = {lx, ly, lz}; 
	//GLfloat LightPosition[] = {lx, ly, lz, lw};
	//VEC3 LightPosition(lx, ly, lz);
}



void world::RenderScene()
{

	//glutSetWindow(WindowID);
	//gl::en

	//camera.RotateLocalY(0.001f);

	//camera.MoveRight(-0.03f);




	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	//gl::ClearDepth(1.0f);

	gl::UseProgram(o_progs.ShaderObject);





	//InitLights();


	/*
	//gl::UseProgram(o_progs.ShaderObject );
	GLint uniformLoc1 = gl::GetUniformLocation( o_progs.ShaderObject, "LightPosition_worldspace");
	if (uniformLoc1 != -1)
	{
	//cout << "LIGHTS " << endl;
	gl::Uniform3fv(uniformLoc1, 1, &LightPosition[0]);
	}
	*/


	/*
	GLint uniformLoc2 = gl::GetUniformLocation( o_progs.ShaderObject, "v_SkyC");
	if (uniformLoc2 != -1)
	{
	gl::Uniform3fv(uniformLoc2, 1, ColorS);
	}
	//cout << "uniform 2: " << uniformLoc2 << endl;

	GLint uniformLoc3 = gl::GetUniformLocation( o_progs.ShaderObject, "v_GroundC");
	if (uniformLoc3 != -1)
	{
	gl::Uniform3fv(uniformLoc3, 1, ColorG);
	}
	//cout << "uniform 3: " << uniformLoc3 << endl;
	*/





	stuff.Magic(true);
	//stuff.DrawAll();

	//gl::UseProgram(0);


	//gl::get

	//gl::Flush();
	//

	//VSGLInfoLib::getVAOInfo(VertexArrayID);

	glutSwapBuffers();
	//glutPostRedisplay();
	//gl::Flush();
	//gl::

}

