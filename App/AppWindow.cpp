#include "AppWindow.h"
#include "../Polygon.h"

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

	this->polygons = std::vector<Nico::Polygon>();

	std::vector<std::vector<vertex>> v  = {
		{
			{-0.2f, 0.5f, 0.0f,  1,0,1},
			{-0.2f, 0.9f, 0.0f,   1,1,0},
			{0.2f,  0.5f, 0.0f,   1,0,1},
			{0.2f, 0.9f, 0.0f,    0,1,1},
		},

		{
			{0.f, -0.2f, 0.0f,  1,1,0},
			{0.f, 0.2f, 0.0f,   0,1,0},
			{0.4f, -0.2f, 0.0f,   0,1,0},
			{0.4f, 0.2f, 0.0f,    0,1,1},
		},

		{
			{-0.8f, -0.2f, 0.0f,  1,1,0},
			{-0.8f, 0.2f, 0.0f,   1,0,0},
			{-0.4f, -0.2f, 0.0f,   1,0,0},
			{-0.4f, 0.2f, 0.0f,    1,1,0},
		},


	};

	this->m_vb = GraphicsEngine::get()->createVertexBuffer();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	this->m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();



	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	this->m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//this->m_vb->load(strip_list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	

	for (int i = 0; i < v.size(); i++) {
		Nico::Polygon poly;
		poly.init(v[i]);
		poly.load(shader_byte_code, size_shader);
		this->polygons.push_back(poly);
	}

	GraphicsEngine::get()->releaseCompiledShader();

}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,  0, 0.3f, 0.4f, 1);


	RECT rc = this->getClientWindowRect();

	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(this->m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(this->m_ps);


	for (auto i : this->polygons) {
		i.draw();
	}



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
