#pragma once

#include "../Game Engine/Window/Window.h"
#include "../Game Engine/Graphics Engine/GraphicsEngine.h"
#include "../Game Engine/Graphics Engine/SwapChain/SwapChain.h"
#include "../Game Engine/Graphics Engine/DeviceContext/DeviceContext.h"
#include "../Game Engine/Graphics Engine/VertexBuffer/VertexBuffer.h"
#include "../Game Engine/Graphics Engine/VertexShader/VertexShader.h"
#include "../Game Engine/Graphics Engine/PixelShader/PixelShader.h"
#include "../Game Engine/Graphics Engine/ConstantBuffer/ConstantBuffer.h"
#include "../Game Engine/Graphics Engine/IndexBuffer/IndexBuffer.h"
#include "../Game Engine/Input System/InputListener.h"

#include <vector>
#include "../Game Engine/Graphics Engine/Cube/Cube.h"
#include "../Quad.h"
#include "../ScreenCapture.h"


class AppWindow : public Window, public InputListener {
	
	private:
		SwapChain* m_swap_chain;
		ScreenCapture* m_screen_capture;
		std::vector<Cube*> cubes;
		Transform camera_transform;

		Cube* c;
		Cube* c1;
		Cube* c2;
		Quad* q;

	private:
		unsigned long m_old_time = 0;
		float m_delta_time = 0;
		float m_angle = 0;

		float xRot = 0.f;
		float yRot = 0.f;
		float zRot = 0.f;

		float multiplier = 2.f;
		float scale = 0.1f;
		bool first = true;


		float updatetransforms = false;
	public:
		AppWindow();
		~AppWindow();

		// Inherited via Window
		void OnCreate() override;
		void OnUpdate() override;
		void OnDestroy() override;

		void OnFocus() override;
		void OnKillFocus() override;

		void PickAndDrag();

	public:
		void UpdateQuadPosition();

		// Inherited via InputListener
		void onKeyDown(int key) override;
		void onKeyUp(int key) override;

		// Inherited via InputListener
		void onMouseMove(const Point& delta_mouse_point, const Point& mouse_pos) override;

		// Inherited via InputListener
		void onLeftMouseDown(const Point& delta_mouse_point) override;
		void onLeftMouseUp(const Point& delta_mouse_point) override;
		void onRightMouseDown(const Point& delta_mouse_point) override;
		void onRightMouseUp(const Point& delta_mouse_point) override;
};