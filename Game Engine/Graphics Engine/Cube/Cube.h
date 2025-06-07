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
#include <vector>
#include "../Transform/Transform.h"

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
		std::vector<vertex> cube_list;
		std::vector<unsigned int> index_list;

		float pace = 0.1f;
		float dir = 1.f;

	public:
		Transform m_transform;

	public:
		std::string m_name;
		Vector3D pos;

	private:
		IndexBuffer* m_ib;
		VertexBuffer* m_vb;

		VertexShader* m_vs;
		PixelShader* m_ps;

		ConstantBuffer* m_cb;
		
	public:
		Cube();
		Cube(std::string name);

		bool load();
		bool release();

		void Draw();
		void Update(float delta_time, Matrix4x4 view_matrix, Matrix4x4 projection_matrix);

		
};

