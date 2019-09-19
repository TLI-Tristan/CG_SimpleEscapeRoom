#include "SceneAssignment02.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"

SceneAssignment02::SceneAssignment02()
{
}

SceneAssignment02::~SceneAssignment02()
{
}

void SceneAssignment02::Init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	glEnable(GL_CULL_FACE);

	camera.Init(Vector3(10, 10, 30), Vector3(0, 0, 0), Vector3(0, 1, 0));

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	//Load vertex and fragment shaders

	//m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Blending.fragmentshader");
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");

	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");

	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");

	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
	m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
	m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
	m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");

	m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
	m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
	m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID, "lights[2].cosInner");
	m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID, "lights[2].exponent");


	m_parameters[U_LIGHT3_POSITION] = glGetUniformLocation(m_programID, "lights[3].position_cameraspace");
	m_parameters[U_LIGHT3_COLOR] = glGetUniformLocation(m_programID, "lights[3].color");
	m_parameters[U_LIGHT3_POWER] = glGetUniformLocation(m_programID, "lights[3].power");
	m_parameters[U_LIGHT3_KC] = glGetUniformLocation(m_programID, "lights[3].kC");
	m_parameters[U_LIGHT3_KL] = glGetUniformLocation(m_programID, "lights[3].kL");
	m_parameters[U_LIGHT3_KQ] = glGetUniformLocation(m_programID, "lights[3].kQ");

	m_parameters[U_LIGHT3_TYPE] = glGetUniformLocation(m_programID, "lights[3].type");
	m_parameters[U_LIGHT3_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[3].spotDirection");
	m_parameters[U_LIGHT3_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[3].cosCutoff");
	m_parameters[U_LIGHT3_COSINNER] = glGetUniformLocation(m_programID, "lights[3].cosInner");
	m_parameters[U_LIGHT3_EXPONENT] = glGetUniformLocation(m_programID, "lights[3].exponent");


	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");


	glUseProgram(m_programID);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	light[0].type = Light::LIGHT_POINT;
	light[0].position.Set(-470, -20, 160);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1; 
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	light[1].type = Light::LIGHT_SPOT;
	light[1].position.Set(2, 144, 0);
	light[1].color.Set(2, 144, 0);
	light[1].power = 0;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 1.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);

	light[2].type = Light::LIGHT_SPOT;
	light[2].position.Set(-160, -30, -198);
	light[2].color.Set(255, 255, 255);
	light[2].power = 0.5;
	light[2].kC = 1.f;
	light[2].kL = 0.01f;
	light[2].kQ = 0.001f;
	light[2].cosCutoff = cos(Math::DegreeToRadian(3));
	light[2].cosInner = cos(Math::DegreeToRadian(1));
	light[2].exponent = 3.f;
	light[2].spotDirection.Set(-1.45f, 0.15f, -1.f);

	light[3].type = Light::LIGHT_SPOT;
	light[3].position.Set(camera.position.x, camera.position.y, camera.position.z);	//position changes
	light[3].color.Set(255, 255, 255);
	light[3].power = 0.2;
	light[3].kC = 1.f;
	light[3].kL = 0.01f;
	light[3].kQ = 0.001f;
	light[3].cosCutoff = cos(Math::DegreeToRadian(10));
	light[3].cosInner = cos(Math::DegreeToRadian(2));
	light[3].exponent = 3.f;
	light[3].spotDirection.Set(1.f, 0.f, 0.f); //direction changes too when player move

	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);

	glUniform1i(m_parameters[U_LIGHT2_TYPE], light[2].type);
	glUniform3fv(m_parameters[U_LIGHT2_COLOR], 1, &light[2].color.r);
	glUniform1f(m_parameters[U_LIGHT2_POWER], light[2].power);
	glUniform1f(m_parameters[U_LIGHT2_KC], light[2].kC);
	glUniform1f(m_parameters[U_LIGHT2_KL], light[2].kL);
	glUniform1f(m_parameters[U_LIGHT2_KQ], light[2].kQ);
	glUniform1f(m_parameters[U_LIGHT2_COSCUTOFF], light[2].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT2_COSINNER], light[2].cosInner);
	glUniform1f(m_parameters[U_LIGHT2_EXPONENT], light[2].exponent);

	glUniform1i(m_parameters[U_LIGHT3_TYPE], light[3].type);
	glUniform3fv(m_parameters[U_LIGHT3_COLOR], 1, &light[3].color.r);
	glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);
	glUniform1f(m_parameters[U_LIGHT3_KC], light[3].kC);
	glUniform1f(m_parameters[U_LIGHT3_KL], light[3].kL);
	glUniform1f(m_parameters[U_LIGHT3_KQ], light[3].kQ);
	glUniform1f(m_parameters[U_LIGHT3_COSCUTOFF], light[3].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT3_COSINNER], light[3].cosInner);
	glUniform1f(m_parameters[U_LIGHT3_EXPONENT], light[3].exponent);

	glUniform1i(m_parameters[U_NUMLIGHTS], 4);

	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID,
		"textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID,
		"textColor");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(255, 255, 255), 1000.f, 600.f, true);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//floor_tile.tga", true);

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(255, 255, 255), 1000.f, 600.f, false);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//ceiling.tga", false);

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(255, 255, 255), 600.f, 300.f, false);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//ceiling.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(255, 255, 255), 600.f, 300.f, false);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//wall_with_door.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(255, 255, 255), 1000.f, 300.f, false);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//wall4.tga", false);

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(255, 255, 255), 1000.f, 300.f, false);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//wall4.tga", false);

	meshList[GEO_MODELCHAIR] = MeshBuilder::GenerateOBJ("model1", "OBJ//chair.obj");
	meshList[GEO_MODELCHAIR]->textureID = LoadTGA("Image//chair.tga", true);

	meshList[GEO_MODELGONG] = MeshBuilder::GenerateOBJ("modelgong", "OBJ//gong.obj");
	meshList[GEO_MODELGONG]->textureID = LoadTGA("Image//gong.tga", true);

	meshList[GEO_MODELLAMPCOVER] = MeshBuilder::GenerateOBJ("modellightcover", "OBJ//lampcover.obj");
	meshList[GEO_MODELLAMPCOVER]->textureID = LoadTGA("Image//lampcover.tga", true);

	meshList[GEO_MODELCEILINGLAMP] = MeshBuilder::GenerateOBJ("modellamp", "OBJ//lamp.obj");
	meshList[GEO_MODELCEILINGLAMP]->textureID = LoadTGA("Image//lampoff.tga", true);

	meshList[GEO_MODELTABLE] = MeshBuilder::GenerateOBJ("modeltable", "OBJ//table.obj");
	meshList[GEO_MODELTABLE]->textureID = LoadTGA("Image//table.tga", true);

	meshList[GEO_MODELSWITCH] = MeshBuilder::GenerateOBJ("modelswitch", "OBJ//switch.obj");
	meshList[GEO_MODELSWITCH]->textureID = LoadTGA("Image//switch.tga", true);

	meshList[GEO_MODELSWITCHCIRCUIT] = MeshBuilder::GenerateOBJ("modelswitchcircuit", "OBJ//switchcircuit.obj");
	meshList[GEO_MODELSWITCHCIRCUIT]->textureID = LoadTGA("Image//switchcircuit.tga", true);

	meshList[GEO_MODELKEY] = MeshBuilder::GenerateOBJ("modelkey", "OBJ//key.obj");
	meshList[GEO_MODELKEY]->textureID = LoadTGA("Image//key.tga", true);

	meshList[GEO_MODELBOOKSHELF] = MeshBuilder::GenerateOBJ("modelbookshelf", "OBJ//bookshelf.obj");
	meshList[GEO_MODELBOOKSHELF]->textureID = LoadTGA("Image//bookshelf.tga", true);

	meshList[GEO_MODELTABLELAMP] = MeshBuilder::GenerateOBJ("modelablelamp", "OBJ//tablelamp.obj");
	meshList[GEO_MODELTABLELAMP]->textureID = LoadTGA("Image//tablelamp.tga", true);

	meshList[GEO_SPOTLIGHT] = MeshBuilder::GenerateOBJ("modelspotlight", "OBJ//spotlight.obj");
	meshList[GEO_SPOTLIGHT]->textureID = LoadTGA("Image//spotlight.tga", true);

	meshList[GEO_SPOTLIGHTCONNECTOR] = MeshBuilder::GenerateOBJ("modelspotlightconnector", "OBJ//spotlightconnector.obj");
	meshList[GEO_SPOTLIGHTCONNECTOR]->textureID = LoadTGA("Image//spotlightconnector.tga", true);

	meshList[GEO_MODELDOOR] = MeshBuilder::GenerateOBJ("modeldoor", "OBJ//door.obj");
	meshList[GEO_MODELDOOR]->textureID = LoadTGA("Image//door.tga", true);

	meshList[GEO_MODELDOORFRAME] = MeshBuilder::GenerateOBJ("modeldoorframe", "OBJ//doorframe.obj");
	meshList[GEO_MODELDOORFRAME]->textureID = LoadTGA("Image//doorframe.tga", true);

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_MODELTORCH] = MeshBuilder::GenerateOBJ("modeldoor", "OBJ//torch.obj");
	meshList[GEO_MODELTORCH]->textureID = LoadTGA("Image//doorframe.tga", true);

	meshList[GEO_RENDERKEY] = MeshBuilder::GenerateQuad("bottom", Color(255, 255, 255), 10.f, 10.f, false);
	meshList[GEO_RENDERKEY]->textureID = LoadTGA("Image//renderkey.tga");

	meshList[GEO_HORRORPIC] = MeshBuilder::GenerateQuad("bottom", Color(255, 255, 255), 70.f, 50.f, false);
	meshList[GEO_HORRORPIC]->textureID = LoadTGA("Image//horror.tga");

	meshList[GEO_CUBECHARACTER] = MeshBuilder::GenerateOBJ("ModelCubeCharacter", "OBJ//cube.obj");
	meshList[GEO_CUBECHARACTER]->textureID = LoadTGA("Image//cube.tga");

	translateswitch = 0;
	rotateswitch = 0;
	rotatedoor = 0;
	translatedoorX = 0;
	translatedoorZ = 0;
	showTime = 0;
	f_fps = 0;
	s_fps = "/0";

	x = "/0";
	y = "/0";
	z = "/0";

	doorOpened = false;
	ceilingLampOn = false;
	ceilingLampWhite = false;
	keyObtained = false;
	keyPressed_Door = false;
	torchLightOn = true;

	delay = 0.0;

}

void SceneAssignment02::Update(double dt)
{
	static const float LSPEED = 10.0f;

	if (Application::IsKeyPressed('1'))
	{
		glEnable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed('2'))
	{
		glDisable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed('3'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (Application::IsKeyPressed('4'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (Application::IsKeyPressed('I') && delay >= 0.2) {	//interacts
		if (camera.position.x >= 365 && camera.position.x <= 450 && //door interaction
			camera.position.y >= -115 && camera.position.y <= 20 &&
			camera.position.z >= -200 && camera.position.z <= -50 ) {
			//interacts

			if (keyObtained == true) {


				rotatedoor = -60;
				translatedoorX = -35;
				translatedoorZ = -20;

				doorOpened = true;
			}

			keyPressed_Door = true;

		}

		if (camera.position.x >= 355 && camera.position.x <= 435 && // key interation
			camera.position.y >= -90 && camera.position.y <= -40 &&
			camera.position.z >= 160 && camera.position.z <= 240) {

			if (keyObtained == false) {
				keyObtained = true;
			}
		}


		if (camera.position.x >= -40 && camera.position.x <= 40 &&		//light interation
			camera.position.y >= -40 && camera.position.y <= 40 &&
			camera.position.z >= -290 && camera.position.z <= -230) {


			if (ceilingLampOn == false) { // if light is off

				ceilingLampOn = true; // turn on light

				if (ceilingLampWhite == true) {

					rotateswitch = 60;
					light[1].power = 1;
					glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);

					meshList[GEO_MODELCEILINGLAMP]->textureID = LoadTGA("Image//lampwhite.tga", true);
				}
				else {

					rotateswitch = 60;
					light[1].power = 1;
					glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);

					meshList[GEO_MODELCEILINGLAMP]->textureID = LoadTGA("Image//lampgreen.tga", true);
					
				}

			}
			else {
				rotateswitch = 0;
				light[1].power = 0;
				glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);

				meshList[GEO_MODELCEILINGLAMP]->textureID = LoadTGA("Image//lampoff.tga", true);

				ceilingLampOn = false;
			}
		}




		delay = 0;

	}
	if (Application::IsKeyPressed('T') && ceilingLampOn == true) {	//change white
		light[1].color.Set(255, 255, 255);
		glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
		meshList[GEO_MODELCEILINGLAMP]->textureID = LoadTGA("Image//lampwhite.tga", true);

		ceilingLampWhite = true;
	}
	if (Application::IsKeyPressed('Y') && ceilingLampOn == true) {	//change Green
		light[1].color.Set(2, 144, 0);
		glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
		meshList[GEO_MODELCEILINGLAMP]->textureID = LoadTGA("Image//lampgreen.tga", true);
		
		ceilingLampWhite = false;
	}

	if (Application::IsKeyPressed('Q')) {	//turn on torch
		
		light[3].power = 0.2;
		glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);

		torchLightOn = true;
	}

	if (Application::IsKeyPressed('E')) {	//turn off torch

		light[3].power = 0;
		glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);

		torchLightOn = false;
	}

	f_fps = 1.0f / dt;

	delay += dt;

	s_fps = std::to_string(f_fps);
	x = std::to_string(camera.position.x);
	y = std::to_string(camera.position.y);
	z = std::to_string(camera.position.z);

	if (torchLightOn == true) {	// torch direction and position change here

		Vector3 view = (camera.target - camera.position).Normalized();

		light[3].position.Set(camera.position.x, camera.position.y, camera.position.z);	//position changes
		light[3].spotDirection.Set(-view.x, -view.y, -view.z);

	}

	if (keyObtained == true && showTime <= 2) {

		showTime += dt;
		
	}

	camera.Update(dt);
	
}

void SceneAssignment02::RenderInteractionGuide() {


	if (camera.position.x >= -40 && camera.position.x <= 40 &&
		camera.position.y >= -40 && camera.position.y <= 40 &&
		camera.position.z >= -290 && camera.position.z <= -230) {

		RenderTextOnScreen(meshList[GEO_TEXT], " Press [i] to switch on/off light", Color(253, 159, 0), 2, 3, 6);
	}

	if (camera.position.x >= 355 && camera.position.x <= 435 &&
		camera.position.y >= -90 && camera.position.y <= -40 &&
		camera.position.z >= 160 && camera.position.z <= 240) {

		if (keyObtained == false) {


			RenderTextOnScreen(meshList[GEO_TEXT], " Press [i] to pick up key", Color(253, 159, 0), 2, 3, 6);

		}

	}

	if (camera.position.x >= 365 && camera.position.x <= 450 &&
		camera.position.y >= -115 && camera.position.y <= 20 &&
		camera.position.z >= -200 && camera.position.z <= -50) {

		if (doorOpened == false) {
			RenderTextOnScreen(meshList[GEO_TEXT], " Press [i] to open the door", Color(253, 159, 0), 2, 3, 6);
			
			if (keyPressed_Door == true) {

				RenderTextOnScreen(meshList[GEO_TEXT], " Door is locked, key is needed", Color(253, 159, 0), 2, 3, 7);

			}
		}

	}
	else {
		keyPressed_Door = false;
	}

}

void SceneAssignment02::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);


	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}

	mesh->Render();

	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

void SceneAssignment02::RenderSkybox() {

	modelStack.PushMatrix();
	modelStack.Translate(0, 148, 0);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_TOP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -148, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	RenderMesh(meshList[GEO_BOTTOM], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -298);
	RenderMesh(meshList[GEO_RIGHT], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 298);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_LEFT], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-498, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_FRONT], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(498, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_BACK], true);
	modelStack.PopMatrix();


}

void SceneAssignment02::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
			Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() *
			characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneAssignment02::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() *
			characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);

}

void SceneAssignment02::RenderTorch() {

	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Translate(65, 15, 0);
	modelStack.Rotate(140, 0, 1, 0);
	modelStack.Rotate(40, 1, 0, 0);
	modelStack.Rotate(20, 0, 0, 1);
	modelStack.Scale(5, 5, 5);
	

	RenderMesh(meshList[GEO_MODELTORCH], true);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

}

void SceneAssignment02::RenderPictureOnScreen(Mesh* mesh, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Translate(x, y, 0);

	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);


	glUniform1i(m_parameters[U_LIGHTENABLED], 0);


	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}

	mesh->Render();

	

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

void SceneAssignment02::RenderChair() {

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(350, -55, 200);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_MODELCHAIR], true);

	modelStack.PopMatrix();
}

void SceneAssignment02::RenderKey() {

	modelStack.PushMatrix();

	modelStack.Translate(405, -90, 200);
	modelStack.Scale(5, 5, 5); // scale back
	RenderMesh(meshList[GEO_MODELKEY], false);

	modelStack.PopMatrix();
}

void SceneAssignment02::RenderDoor() {

	modelStack.PushMatrix();

	modelStack.Translate(497, -65, -150);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 30, 30);
	RenderMesh(meshList[GEO_MODELDOORFRAME], true);

	modelStack.PopMatrix();

	modelStack.PushMatrix();

	modelStack.Translate(497, -65, -150);
	modelStack.Translate(translatedoorX, 0, translatedoorZ);
	modelStack.Rotate(rotatedoor, 0, 1, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 30, 30);

	RenderMesh(meshList[GEO_MODELDOOR], true);

	modelStack.PopMatrix();

}

void SceneAssignment02::RenderGong() {

	modelStack.PushMatrix();

	modelStack.Translate(-440, -52, 200);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_MODELGONG], true);
	modelStack.PopMatrix();

}

void SceneAssignment02::RenderTable() {

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(-460, -140, 180);
	modelStack.Scale(20, 20, 20);
	RenderMesh(meshList[GEO_MODELTABLE], true);
		
	modelStack.PopMatrix();

}

void SceneAssignment02::RenderTableLamp() {

	modelStack.PushMatrix();

	modelStack.Translate(-470, -50, 140);
	modelStack.Scale(12, 12, 12);

	RenderMesh(meshList[GEO_MODELTABLELAMP], true);
	modelStack.PopMatrix();

}

void SceneAssignment02::RenderCeilingLamp() {

	modelStack.PushMatrix();
	modelStack.Translate(0, 145, 0);
	modelStack.Scale(15, 15, 15);
	RenderMesh(meshList[GEO_MODELLAMPCOVER], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(light[1].position.x, light[1].position.y, light[1].position.z);
	modelStack.Scale(15, 15, 14);
	RenderMesh(meshList[GEO_MODELCEILINGLAMP], false);
	modelStack.PopMatrix();

}

void SceneAssignment02::RenderSwitch() {

	modelStack.PushMatrix();

	modelStack.Translate(0, 0, -297);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_MODELSWITCHCIRCUIT], true);

		modelStack.PushMatrix();

		modelStack.Rotate(rotateswitch, 1, 0, 0);
		RenderMesh(meshList[GEO_MODELSWITCH], true);

		modelStack.PopMatrix();

	modelStack.PopMatrix();

}

void SceneAssignment02::RenderBookShelf() {

	modelStack.PushMatrix();

	modelStack.Translate(-460, -140, -198);
	modelStack.Scale(20, 20, 20);
	RenderMesh(meshList[GEO_MODELBOOKSHELF], true);

	modelStack.PopMatrix();

	

}

void SceneAssignment02::RenderSpotLight() {

	modelStack.PushMatrix();

	modelStack.Translate(-460, -40, -198);
	modelStack.Rotate(-30, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_SPOTLIGHTCONNECTOR], true);

		modelStack.PushMatrix();

		RenderMesh(meshList[GEO_SPOTLIGHT], false);

		modelStack.PopMatrix();

	modelStack.PopMatrix();
}

void SceneAssignment02::RenderLight() {


	if (light[0].type == Light::LIGHT_POINT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (light[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}

	 if (light[2].type == Light::LIGHT_SPOT)
	 {
		 Position lightPosition_cameraspace = viewStack.Top() * light[2].position;
		 glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace.x);
		 Vector3 spotDirection_cameraspace = viewStack.Top() * light[2].spotDirection;
		 glUniform3fv(m_parameters[U_LIGHT2_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	 }

	
	if (light[3].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[3].position;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[3].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT3_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}

}

void SceneAssignment02::Render()
{
	//Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	modelStack.LoadIdentity();

	modelStack.PushMatrix();
	RenderLight();
	modelStack.PopMatrix();

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);

	modelStack.LoadIdentity();


	modelStack.PushMatrix();

	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_CUBECHARACTER], true);

	modelStack.PopMatrix();


	RenderBookShelf();

	RenderSpotLight();

	RenderCeilingLamp();

	RenderTableLamp();

	RenderTable();

	RenderSwitch();

	RenderGong();

	RenderDoor();

	RenderChair();

	RenderTorch();

	


	if (keyObtained == true && showTime <= 2) {

		RenderPictureOnScreen(meshList[GEO_HORRORPIC], 40, 30);

	}

	RenderSkybox();

	if (keyObtained == false) {

		RenderKey();
	}
	else {
		RenderPictureOnScreen(meshList[GEO_RENDERKEY], 70, 6);
	}

	RenderInteractionGuide();

	if (doorOpened == true) {
		modelStack.PushMatrix();

		modelStack.Translate(499, -65, -185);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(4, 4, 4);
		RenderText(meshList[GEO_TEXT], "CONGRATULATIONS YOU", Color(220, 20, 60));

		modelStack.PopMatrix();

		modelStack.PushMatrix();

		modelStack.Translate(499, -69, -185);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(4, 4, 4);
		RenderText(meshList[GEO_TEXT], "MIGHT STILL DIE", Color(220, 20, 60));

		modelStack.PopMatrix();
	}


	RenderTextOnScreen(meshList[GEO_TEXT], "X:", Color(220, 20, 60), 2, 1, 4);
	RenderTextOnScreen(meshList[GEO_TEXT], x, Color(220, 20, 60), 2, 3, 4);

	RenderTextOnScreen(meshList[GEO_TEXT], "Y:", Color(220, 20, 60), 2, 1, 3);
	RenderTextOnScreen(meshList[GEO_TEXT], y, Color(220, 20, 60), 2, 3, 3);

	RenderTextOnScreen(meshList[GEO_TEXT], "Z:", Color(220, 20, 60), 2, 1, 2);
	RenderTextOnScreen(meshList[GEO_TEXT], z, Color(220, 20, 60), 2, 3, 2);

	RenderTextOnScreen(meshList[GEO_TEXT],s_fps, Color(0, 255, 0), 2, 5, 1);
	RenderTextOnScreen(meshList[GEO_TEXT], "FPS: ", Color(0, 255, 0), 2, 1, 1);

}

void SceneAssignment02::Exit()
{
	// Cleanup VBO here
	glDeleteProgram(m_programID);

}
