#include "AppWindow.h"
#include <Windows.h>
#include "../Game Engine/Math/Vector3D.h"
#include "../Game Engine/Math/Matrix4x4.h"
#include "../Game Engine/Input System/InputSystem.h"
#include <iostream>
#include <utility>
#include <cstdlib>



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

	for (int i = 0; i < 5; i++) {
		cubes.push_back(new Cube());
		cubes[i]->load();

		Matrix4x4 temp;
		
		temp.SetTranslation(Vector3D(-2 + i * 1.5f, 0, 0));
		cubes[i]->m_transform *= temp;
		

		temp.SetScale(Vector3D(0.2f, 0.2f, 0.2f));
		cubes[i]->m_transform *= temp;
	}

}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();

	InputSystem::get()->Update();

	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,  0, 0.3f, 0.4f, 1);


	RECT rc = this->getClientWindowRect();

	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	unsigned long new_time = 0;

	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();

	m_angle += 0.1 * m_delta_time;

	Matrix4x4 temp;
	temp.setRotationX(m_delta_time);
	
	for(auto c: cubes){
		c->m_transform *= temp;
	}

	temp.SetIdentity();
	temp.setRotationY(m_delta_time);

	for (auto c : cubes) {
		c->m_transform *= temp;
	}

	//draw here 
	for (auto c : cubes) {
		c->Update(m_delta_time, this->getClientWindowRect());
		c->Draw();
	}
		
		

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

void AppWindow::onKeyDown(int key)
{
	/*
	float turn_speed = m_delta_time * multiplier;
	switch (key) {
		case 'W': xRot -= turn_speed; break;
		case 'S': xRot += turn_speed;  break;

		case 'A': yRot -= turn_speed; break;
		case 'D': yRot += turn_speed;  break;

		case 'Q': zRot -= turn_speed; break;
		case 'E':  zRot += turn_speed;  break;
	}
	*/
}

void AppWindow::onKeyUp(int key)
{
	
}

void AppWindow::onMouseMove(const Point& delta_mouse_point)
{

	xRot -= delta_mouse_point.m_y * m_delta_time ;
	yRot -= delta_mouse_point.m_x * m_delta_time ;

}

void AppWindow::onLeftMouseDown(const Point& delta_mouse_point)
{
	std::cout << "Left Click!\n";

	Cube* c = new Cube();
	c->load();
	cubes.push_back(c);

	int rand_x = rand() % 5 + 1;
	int rand_y = rand() % 5 + 1;
	int rand_z = rand() % 5 + 1;

	Matrix4x4 temp;
	temp.SetTranslation(Vector3D(rand_x, rand_y, rand_z));
	c->m_transform *= temp;

	temp.SetScale(Vector3D(0.2f, 0.2f, 0.2f));
	c->m_transform *= temp;

	/*
	RECT rc = this->getClientWindowRect();

	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	float ndc_X = (delta_mouse_point.m_x / width) * 2 - 1;
	float ndc_y = 1 - (delta_mouse_point.m_y / height) * 2;

	Vector3D vec = Vector3D(ndc_X, ndc_y, 0);
	*/


}

void AppWindow::onLeftMouseUp(const Point& delta_mouse_point)
{
}

void AppWindow::onRightMouseDown(const Point& delta_mouse_point)
{
	std::cout << "Right Click!\n";
	scale -= 0.1f;
	if(scale < 0.1f)
		scale = 0.1f;
}

void AppWindow::onRightMouseUp(const Point& delta_mouse_point)
{
}

