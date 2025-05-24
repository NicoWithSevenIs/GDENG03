#pragma once

class VertexShader {
	public:
		VertexShader();
		~VertexShader();
		bool release();
	private:
		bool init();
};