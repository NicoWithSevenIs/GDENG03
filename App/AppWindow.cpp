#include "AppWindow.h"
#include <Windows.h>
#include "../Game Engine/Math/Vector3D.h"
#include "../Game Engine/Math/Matrix4x4.h"
#include "../Game Engine/Input System/InputSystem.h"
#include <iostream>
#include <utility>
struct vertex {
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	float m_angle;
};

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::OnCreate()
{
	Window::OnCreate();



	GraphicsEngine::get()->init();
	this->m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	this->m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex cube_list[] = {
		{Vector3D(-0.5f, -0.5f, -0.5f), Vector3D(0, 1, 0), Vector3D(1, 0, 0)},
		{Vector3D(-0.5f,  0.5f, -0.5f), Vector3D(1, 0, 1), Vector3D(0, 0, 1)},
		{Vector3D(0.5f,  0.5f, -0.5f), Vector3D(0, 0, 1), Vector3D(1, 1, 0)},
		{Vector3D(0.5f, -0.5f, -0.5f), Vector3D(1, 1, 1), Vector3D(0, 1, 1)},
		{Vector3D(0.5f, -0.5f,  0.5f), Vector3D(0, 1, 0), Vector3D(1, 0, 1)},
		{Vector3D(0.5f,  0.5f,  0.5f), Vector3D(1, 0, 0), Vector3D(1, 1, 1)},
		{Vector3D(-0.5f,  0.5f,  0.5f), Vector3D(0, 0, 1), Vector3D(0, 1, 0)},
		{Vector3D(-0.5f, -0.5f,  0.5f), Vector3D(1, 1, 0), Vector3D(0, 0, 0)},
	};

	unsigned int index_list[] =
	{
		// FRONT SIDE
		0, 1, 2,   // FIRST TRIANGLE
		2, 3, 0,   // SECOND TRIANGLE

		// BACK SIDE
		4, 5, 6,
		6, 7, 4,

		// TOP SIDE
		1, 6, 5,
		5, 2, 1,

		// BOTTOM SIDE
		7, 0, 3,
		3, 4, 7,

		// RIGHT SIDE
		3, 2, 5,
		5, 4, 3,

		// LEFT SIDE
		7, 6, 1,
		1, 0, 7
	};

	this->m_vb = GraphicsEngine::get()->createVertexBuffer();
	this->m_ib = GraphicsEngine::get()->createIndexBuffer();



	UINT size_list = ARRAYSIZE(cube_list);
	UINT size_index_list = ARRAYSIZE(index_list);


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	this->m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	this->m_vb->load(cube_list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	this->m_ib->load(index_list, size_index_list);


	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	this->m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);


	GraphicsEngine::get()->releaseCompiledShader();

	constant cc;
	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));



}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();

	InputSystem::get()->Update();

	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,  0, 0.3f, 0.4f, 1);


	RECT rc = this->getClientWindowRect();

	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	UpdateQuadPosition();

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(this->m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(this->m_ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedList(m_ib->getSizeIndexList(), 0, 0);

	this->m_swap_chain->present(true);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	this->m_vb->release();
	this->m_swap_chain->release();
	this->m_vs->release();
	this->m_ps->release();
	this->m_ib->release();
	this->m_cb->release();

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
	unsigned long new_time = 0;

	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();

	m_angle += m_delta_time;

	constant cc;
	cc.m_angle = m_angle;

	Matrix4x4 temp;

	
	cc.m_world.SetScale(Vector3D(scale,scale,scale));

	
	temp.SetIdentity();
	temp.setRotationX(xRot);
	cc.m_world *= temp;

	temp.SetIdentity();
	temp.setRotationY(yRot);
	cc.m_world *= temp;

	temp.SetIdentity();
	temp.setRotationZ(zRot);
	cc.m_world *= temp;


	//temp.SetTranslation(Vector3D());




	cc.m_view.SetIdentity();
	cc.m_proj.setOrthoLH(
		(this->getClientWindowRect().right - this->getClientWindowRect().left)/400.f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top)/400.f,
		-4.f,
		4.f
	);

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
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
	scale += 0.5f;
}

void AppWindow::onLeftMouseUp(const Point& delta_mouse_point)
{
}

void AppWindow::onRightMouseDown(const Point& delta_mouse_point)
{
	std::cout << "Right Click!\n";
	scale -= 0.5f;
	if(scale < 1.f)
		scale = 1.f;
}

void AppWindow::onRightMouseUp(const Point& delta_mouse_point)
{
}

