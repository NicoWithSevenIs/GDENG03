#pragma once

#include "../Game Engine/Window/Window.h"
#include "../Game Engine/Graphics Engine/GraphicsEngine.h"
#include "../Game Engine/Graphics Engine/SwapChain/SwapChain.h"
#include "../Game Engine/Graphics Engine/DeviceContext/DeviceContext.h"
#include "../Game Engine/Graphics Engine/VertexBuffer/VertexBuffer.h"
#include "../Game Engine/Graphics Engine/VertexShader/VertexShader.h"
#include "../Game Engine/Graphics Engine/PixelShader/PixelShader.h"
#include "../Game Engine/Graphics Engine/ConstantBuffer/ConstantBuffer.h"

class AppWindow : public Window {
	
	private:
		SwapChain* m_swap_chain;
		VertexBuffer* m_vb;
		VertexShader* m_vs;
		PixelShader* m_ps;
		ConstantBuffer* m_cb;

	private:
		unsigned long m_old_time = 0;
		float m_delta_time = 0;
		float m_angle = 0;

	public:
		AppWindow();
		~AppWindow();

		// Inherited via Window
		void OnCreate() override;
		void OnUpdate() override;
		void OnDestroy() override;
};