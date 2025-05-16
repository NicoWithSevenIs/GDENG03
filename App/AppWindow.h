#pragma once

#include "../Game Engine/Window/Window.h"
#include "../Game Engine/Graphics Engine/GraphicsEngine.h"
#include "../Game Engine/Graphics Engine/SwapChain/SwapChain.h"

class AppWindow : public Window {
	
	private:
		SwapChain* m_swap_chain;

	public:
		AppWindow();
		~AppWindow();

		// Inherited via Window
		void OnCreate() override;
		void OnUpdate() override;
		void OnDestroy() override;
};