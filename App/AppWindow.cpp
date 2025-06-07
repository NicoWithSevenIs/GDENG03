#include "AppWindow.h"
#include <Windows.h>
struct vec3 {
	float x,y,z;
};

struct vertex {
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};

__declspec(align(16))
struct constant
{
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

	/*
	vertex list[] = {
		{-0.5f, -0.5f, 0.0f,  1,0,0},
		{0.0f, 0.5f, 0.0f,    0,1,0},
		{0.5f, -0.5f, 0.0f,   0,0,1},
	};

	vertex quad_list[] = {
		{-0.5f, -0.5f, 0.0f},
		{-0.5f, 0.5f, 0.0f},
		{0.5f, 0.5f, 0.0f},

		{0.5f, 0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f},
		{-0.5f, -0.5f, 0.0f},
	};
	*/

	vertex strip_list[] = {
		{-0.5f, -0.5f, 0.0f,	-0.32f, -0.11f, 0.0f,	  0,0,0,  0,1,0	},
		{-0.5f, 0.5f, 0.0f,		-0.11f, 0.78f, 0.0f,	  1,1,0,  1,1,0 },
		{0.5f, -0.5f, 0.0f,		0.75f, -0.73f, 0.0f,	  0,0,1,  1,0,0 },
		{0.5f, 0.5f, 0.0f,		0.88f, 0.77f, 0.0f,		  1,1,1,  0,0,1 },
	};

	this->m_vb = GraphicsEngine::get()->createVertexBuffer();

	UINT size_list = ARRAYSIZE(strip_list);


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	this->m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	this->m_vb->load(strip_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	this->m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);


	GraphicsEngine::get()->releaseCompiledShader();

	constant cc;
	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));



}

#include <iostream>



void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,  0, 0.3f, 0.4f, 1);


	RECT rc = this->getClientWindowRect();

	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	if (sspeed < max_speed) {
		sspeed += Time::getDeltaTime() * 0.3;
	}
		
	else sspeed = 0;

	m_angle += 1.57f * Time::getDeltaTime() * sspeed;

	constant cc;
	cc.m_angle = m_angle;



	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

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
