#include "AppWindow.h"

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
}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	this->m_swap_chain->release();
	GraphicsEngine::get()->release();
}
