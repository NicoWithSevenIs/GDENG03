#pragma once
#include <Windows.h>

class Window {

	protected:
		HWND m_hwnd;
		bool m_is_running;

	public:
		Window();
		~Window();

		bool init();
		bool broadcast();
		bool release();
		bool isRunning();

		RECT getClientWindowRect();
		void setHWND(HWND hwnd);

		virtual void OnCreate();
		virtual void OnUpdate();
		virtual void OnDestroy();

};