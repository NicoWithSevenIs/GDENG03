#include "AppWindow.h"
#include <Windows.h>
#include "../Game Engine/Math/Vector3D.h"
#include "../Game Engine/Math/Matrix4x4.h"
#include "../Game Engine/Input System/InputSystem.h"
#include <iostream>
#include <utility>
#include <cstdlib>
#include <algorithm>
#include <DirectXMath.h>
#include <corecrt_math_defines.h>
#include "../Time.h"



AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}



void AppWindow::OnCreate()
{
	Window::OnCreate();

	srand(time(0));

	GraphicsEngine::get()->init();
	this->m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	this->m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	std::cout << "Height: " << rc.bottom - rc.top <<std::endl;
	std::cout << "Width: " << rc.right - rc.left << std::endl;


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(m_hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getDevice(), GraphicsEngine::get()->getImmediateDeviceContext()->getContext());




	m_screen_capture = new ScreenCapture();
	m_screen_capture->init(m_swap_chain->get(), GraphicsEngine::get()->getDevice(), 
		GraphicsEngine::get()->getImmediateDeviceContext()->getContext());

	Cube* c = new Cube();
	c->load();
	cubes.push_back(c);
	c->doOnUpdate = [=]() {
		c->m_transform.m_rotation.m_x += Time::deltaTime();
		c->m_transform.m_rotation.m_y += Time::deltaTime();
		c->m_transform.m_rotation.m_z += Time::deltaTime();
	};

	m_camera = new Camera();
	m_camera->m_transform.m_translation = Vector3D(0, 0, -3);
	m_camera->setSubject(c);
	//camera_transform.m_translation = Vector3D(0,0,-3);

}

#pragma region Spaghetti

bool isMoving = false;
float dir = 0.f;
float r = 0.f;
float up = 0.f;

Matrix4x4 projection_matrix;
Matrix4x4 view_matrix;
float fov = 1.57f;
Vector3D ray;

float speed = 0;
#pragma endregion Spaghetti


void AppWindow::OnUpdate()
{
	Window::OnUpdate();

	
	InputSystem::get()->Update();
	//InputSystem::get()->ShowCursor(false);

	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,  0, 0.3f, 0.4f, 1);

	RECT rc = this->getClientWindowRect();
	float width = rc.right - rc.left;
	float height = rc.bottom - rc.top;

	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	Matrix4x4 camera_matrix = this->camera_transform.GetTransformationMatrix();
	this->camera_transform.m_rotation = Vector3D(xRot, yRot, 0);
	m_camera->Update(Time::deltaTime(), view_matrix, projection_matrix);
	//this->camera_transform.m_translation.m_x += Time::deltaTime();


	view_matrix = m_camera->getViewMatrix();
	view_matrix.inverse();

	projection_matrix.setPerspectiveFovLH(fov, width / height, 0.1f, 100.0f);


	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//ImGui::ShowDemoWindow(); // Show demo window! :)


	if (m_screen_capture->CanPrompt()) {
		ImGui::SetNextWindowSize(ImVec2(200, 60));
		ImGui::Begin("Record Window");
		if (ImGui::Button("Record")) {
			m_screen_capture->CaptureScreen();
		}
		ImGui::End();
	}


	/*
	Matrix4x4 camera_matrix = this->camera_transform.GetTransformationMatrix();
	Vector3D forward = camera_matrix.getLocalZDirection() * Time::deltaTime() * dir;
	Vector3D right = camera_matrix.getLocalXDirection() * Time::deltaTime() * r;

	this->camera_transform.m_translation = this->camera_transform.m_translation + forward + right + Vector3D(0, Time::deltaTime() * up, 0);
	this->camera_transform.m_rotation = Vector3D(xRot, yRot, 0);
	
	//this->camera_transform.m_translation.m_x += Time::deltaTime();
	

	view_matrix = Matrix4x4(this->camera_transform.GetTransformationMatrix());
	view_matrix.inverse();

	projection_matrix.setPerspectiveFovLH(fov, width/height , 0.1f, 100.0f);
	*/
	/*
	projection_matrix.setOrthoLH(
		(rc.right - rc.left) / 400.f,
		(rc.bottom - rc.top) / 400.f,
		-4.f,
		4.f
	);
	*/
	

	//draw here 
	for (auto c : cubes) {
		c->Update(Time::deltaTime(), view_matrix, projection_matrix);
		c->Draw();
	}



	//if(first)
		//first = false;
	



	m_screen_capture->Update();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	this->m_swap_chain->present(true);



}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	this->m_swap_chain->release();

	for(auto c: cubes)
		c->release();

	GraphicsEngine::get()->release();
}

void AppWindow::OnFocus()
{
	std::cout << "Gained Focus\n";
	InputSystem::get()->AddListener(this);
}

void AppWindow::OnKillFocus()
{
	std::cout << "Lost Focus\n";
	InputSystem::get()->RemoveListener(this);
	InputSystem::get()->first = true;
}

void AppWindow::UpdateQuadPosition()
{


}


int transform_state = 0;
float transform_speed_multiplier = 16;

void AppWindow::onKeyDown(int key)
{
	/*
	float turn_speed = Time::deltaTime() * multiplier;
	switch (key) {

		case 'W': dir = 1.f; break;
		case 'S': dir = -1.f;  break;

		case 'A': r = -1.f; break;
		case 'D': r = 1.f;  break;
		
		case 'Q': up = -1.f; break;
		case 'E':  up = 1.f;  break;


	}
	*/
}

void AppWindow::onKeyUp(int key)
{
	/*
	switch (key) {
		case 'W': 
		case 'S': dir = 0.f;  break;
		case 'A': 
		case 'D': r = 0.f;  break;
		case 'Q': 
		case 'E': up = 0.f;  break;
	

		case 'R':
			
			//m_screen_capture->CaptureScreen();
			break;


	}
	*/

	float move_speed = transform_speed_multiplier * Time::deltaTime();
	float rot_speed = Time::deltaTime() * multiplier;

	switch (key)
	{
	case 'W': m_camera->m_transform.m_translation.m_z -= move_speed; break;
	case 'S': m_camera->m_transform.m_translation.m_z += move_speed; break;
	case 'A': m_camera->m_transform.m_translation.m_x += move_speed; break;
	case 'D': m_camera->m_transform.m_translation.m_x -= move_speed; break;
	case 'Q': m_camera->m_transform.m_translation.m_y -= move_speed; break;
	case 'E': m_camera->m_transform.m_translation.m_y += move_speed; break;

	case VK_LEFT:   m_camera->m_transform.m_rotation.m_y -= rot_speed; break;
	case VK_RIGHT:  m_camera->m_transform.m_rotation.m_y += rot_speed; break;
	case VK_UP:     m_camera->m_transform.m_rotation.m_x -= rot_speed; break;
	case VK_DOWN:   m_camera->m_transform.m_rotation.m_x += rot_speed; break;
	}

	camera_transform.m_rotation.m_x = max(-1.57f, min(1.57f, camera_transform.m_rotation.m_x));
}

//I got the values of the camera transform  by aiming the camera at a certain angle and position then printing it out and forcing the camera to face that way in each update call



Vector3D raydir;
Vector3D rayorigin;


Cube* selected = nullptr;

void AppWindow::onMouseMove(const Point& delta_mouse_point, const Point& mouse_pos)
{
	/*
	xRot -= delta_mouse_point.m_y * Time::deltaTime() * 0.1f ;
	yRot -= delta_mouse_point.m_x * Time::deltaTime() * 0.1f ;

	POINT p = {};
	p.x = mouse_pos.m_x;
	p.y = mouse_pos.m_y;

	Matrix4x4 inverse_view_proj;
	inverse_view_proj.SetIdentity();
	inverse_view_proj *= view_matrix;
	inverse_view_proj *= projection_matrix;
	inverse_view_proj.inverse();

	ScreenToClient(this->m_hwnd, &p);

	//get NDC coordinates
	RECT rc = this->getClientWindowRect();
	float width = rc.right - rc.left;
	float height = rc.bottom - rc.top;

	float ndc_x = std::clamp( (p.x / width) * 2.f - 1.f , -1.f, 1.f);
	float ndc_y = std::clamp( 1.0f - (p.y / height) * 2.0f, -1.f, 1.f);

	Vector3D origin = Vector3D(ndc_x, ndc_y, 0);
	Vector3D far_v = Vector3D(ndc_x, ndc_y, 1);

	//project ray to world space by "reversing the graphics pipeline?" by inverting the view and projection matrix
	rayorigin = Matrix4x4::transform(origin, inverse_view_proj);
	Vector3D rayend = Matrix4x4::transform(far_v, inverse_view_proj);

	//get direction
	raydir = Vector3D::normalize(rayend - rayorigin);

	//translate ray to origin of the ray position
	ray = rayorigin+raydir;


	//some object picking stuff
	if(selected)
		selected->m_transform.m_translation = ray;


	//InputSystem::get()->SetCursorPos({ (int) width /2, (int)height /2});
	*/

	xRot -= delta_mouse_point.m_y * Time::deltaTime() * 0.1f;
	yRot -= delta_mouse_point.m_x * Time::deltaTime() * 0.1f;

	xRot = std::clamp(xRot, -1.57f, 1.57f);

	m_camera->m_transform.m_rotation = Vector3D(xRot, yRot, 0);
}

float z_offset = 0;

void AppWindow::onLeftMouseDown(const Point& delta_mouse_point)
{
	/*
		return;

	//z_offset -= 0.5;
	//create cube at ray position
	Cube* c = new Cube();
	c->load();
	cubes.push_back(c);
	Vector3D newR = Vector3D(ray);
	newR.m_z += z_offset;
	c->m_transform.m_translation = newR;
	c->m_transform.m_scale = Vector3D(0.2f,0.2f,0.2f);

	std::cout << "(" << newR.m_x << "," << newR.m_y << "," << newR.m_z << ")\n";


	*/
}

void AppWindow::onLeftMouseUp(const Point& delta_mouse_point)
{
}

//Möller–Trumbore intersection algorithm. https://en.m.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm

bool Intersects(Vector3D v0, Vector3D v1, Vector3D v2, float dist = 1.f) {

	constexpr float epsilon = std::numeric_limits<float>::epsilon();

	Vector3D edge1 = v1 - v0;
	Vector3D edge2 = v2 - v0;
	Vector3D ray_cross_e2 = Vector3D::Cross(ray * dist, edge2);

	float det = Vector3D::Dot(edge1, ray_cross_e2);

	if(det > -epsilon && det < epsilon)
		return false;

	float inv_det = 1.f / det;
	Vector3D s = rayorigin - v0;
	float u = inv_det * Vector3D::Dot(s, ray_cross_e2);

	if ((u < 0 && abs(u) > epsilon) || (u > 1 && abs(u - 1) > epsilon))
		return false;

	Vector3D s_cross_e1 = Vector3D::Cross(s, edge1);
	float v = inv_det * Vector3D::Dot(ray * dist, s_cross_e1);

	if ((v < 0 && abs(v) > epsilon) || (u + v > 1 && abs(u + v - 1) > epsilon))
		return false;

	float t = inv_det * Vector3D::Dot(edge2, s_cross_e1);

	return t > epsilon && t <= dist;
}

//still buggy
void AppWindow::PickAndDrag() {
	if (!selected) {
		for (auto c : cubes) {

			for (UINT i = 0; i < c->index_list.size() / 3; i++) {
				UINT i0 = c->index_list[i * 3 + 0];
				UINT i1 = c->index_list[i * 3 + 1];
				UINT i2 = c->index_list[i * 3 + 2];

				//std::cout << i0 << ","  << i1 << "," << i2 << "\n";

				Vector3D v0 = c->cube_list[i0].position;
				Vector3D v1 = c->cube_list[i1].position;
				Vector3D v2 = c->cube_list[i2].position;

				Matrix4x4 translation;
				translation.SetTranslation(c->m_transform.m_translation);

				v0 = v0 + c->m_transform.m_translation;
				v1 = v1 + c->m_transform.m_translation;
				v2 = v2 + c->m_transform.m_translation;


				if (Intersects(v0, v1, v2, 100)) {
					selected = c;
					break;
				}

			}


		}
	}
	else selected = nullptr;

}

void AppWindow::onRightMouseDown(const Point& delta_mouse_point)
{
	PickAndDrag();
}

void AppWindow::onRightMouseUp(const Point& delta_mouse_point)
{
	
}

