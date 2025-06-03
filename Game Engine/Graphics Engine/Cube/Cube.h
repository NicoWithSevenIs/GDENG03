#pragma once
#include <d3d11.h>

#include "../../Math/Matrix4x4.h"
#include "../../Math/Vector3D.h"
#include "../IndexBuffer/IndexBuffer.h"
#include "../VertexBuffer/VertexBuffer.h"
#include "../VertexShader/VertexShader.h"
#include "../PixelShader/PixelShader.h"
#include "../ConstantBuffer/ConstantBuffer.h"
#include <string>

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	float m_angle;
};

class Cube {
	
	public:
		Matrix4x4 m_transform;
		std::string m_name;
		Vector3D pos;

	private:
		IndexBuffer* m_ib;
		VertexBuffer* m_vb;

		VertexShader* m_vs;
		PixelShader* m_ps;

		ConstantBuffer* m_cb;
		
		float m_x_rot = 0;
		float m_y_rot = 0;


		

	public:
		Cube();
		Cube(std::string name);

		bool load();
		bool release();

		void Draw();
		void Update(float delta_time, RECT client_rect);
		
};

