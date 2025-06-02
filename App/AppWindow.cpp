#include "AppWindow.h"
#include <Windows.h>
#include "../Game Engine/Math/Vector3D.h"
#include "../Game Engine/Math/Matrix4x4.h"

struct vertex {
	Vector3D position;
	Vector3D position1;
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

	vertex strip_list[] = {
		{Vector3D(-0.5f, -0.5f, 0.0f),	Vector3D(-0.32f, -0.11f, 0.0f),	  Vector3D(0,0,0),  Vector3D(0,0,0)},
		{Vector3D(-0.5f, 0.5f, 0.0f),	Vector3D(-0.11f, 0.78f, 0.0f),	  Vector3D(1,1,0),  Vector3D(0,0,0)},
		{Vector3D(0.5f, -0.5f, 0.0f),	Vector3D(0.75f, -0.73f, 0.0f),	  Vector3D(0,0,1),  Vector3D(0,0,0)},
		{Vector3D(0.5f, 0.5f, 0.0f),	Vector3D(0.88f, 0.77f, 0.0f),	  Vector3D(1,1,1),  Vector3D(0,0,0)},
	};

	this->m_vb = GraphicsEngine::get()->createVertexBuffer();

	UINT size_list = ARRAYSIZE(strip_list);


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	this->m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	this->m_vb->load(strip_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

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
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,  0, 0.3f, 0.4f, 1);


	RECT rc = this->getClientWindowRect();

	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	UpdateQuadPosition();

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(this->m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(this->m_ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);

	this->m_swap_chain->present(true);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	this->m_vb->release();
	this->m_swap_chain->release();
	this->m_vs->release();
	this->m_ps->release();
	GraphicsEngine::get()->release();
}

void AppWindow::UpdateQuadPosition()
{
	unsigned long new_time = 0;

	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();

	m_angle += m_delta_time;

	//if(m_angle > 1.f)
		//m_angle = 0;

	constant cc;
	cc.m_angle = m_angle;

	//cc.m_world.SetTranslation(Vector3D::lerp(Vector3D(-2,-2,0), Vector3D(2,2,0), m_angle));

	Matrix4x4 temp;
	cc.m_world.SetIdentity();
	temp.SetIdentity();
	
	cc.m_world.SetScale(Vector3D::lerp(Vector3D(0.5f, 0.5f, 0), Vector3D(2, 2, 0), m_angle * 0.05));
	temp.SetTranslation(Vector3D::lerp(Vector3D(-2, -2, 0), Vector3D(2, 2, 0), m_angle * 0.1));

	cc.m_world *= temp;

	cc.m_view.SetIdentity();
	cc.m_proj.setOrthoLH(
		(this->getClientWindowRect().right - this->getClientWindowRect().left)/400.f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top)/400.f,
		-4.f,
		4.f
	);

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}
