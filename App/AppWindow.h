#pragma once

#include "../Game Engine/Window/Window.h"
#include "../Game Engine/Graphics Engine/GraphicsEngine.h"
#include "../Game Engine/Graphics Engine/SwapChain/SwapChain.h"
#include "../Game Engine/Graphics Engine/DeviceContext/DeviceContext.h"
#include "../Game Engine/Graphics Engine/VertexBuffer/VertexBuffer.h"
#include "../Game Engine/Graphics Engine/VertexShader/VertexShader.h"
#include "../Game Engine/Graphics Engine/PixelShader/PixelShader.h"

class AppWindow : public Window {
	
	private:
		SwapChain* m_swap_chain;
		VertexBuffer* m_vb;
		VertexShader* m_vs;
		PixelShader* m_ps;

	public:
		AppWindow();
		~AppWindow();

		// Inherited via Window
		void OnCreate() override;
		void OnUpdate() override;
		void OnDestroy() override;
};