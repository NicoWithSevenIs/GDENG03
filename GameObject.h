#pragma once
#include "Game Engine/Math/Vector3D.h"
#include "Game Engine/Math/Matrix4x4.h"
#include "Game Engine/Graphics Engine/Transform/Transform.h"
#include "Game Engine/Graphics Engine/GraphicsEngine.h"
#include "Game Engine/Graphics Engine/DeviceContext/DeviceContext.h"

#include <d3d11.h>
#include <string>

#include "Game Engine/Graphics Engine/IndexBuffer/IndexBuffer.h"
#include "Game Engine/Graphics Engine/VertexBuffer/VertexBuffer.h"
#include "Game Engine/Graphics Engine/VertexShader/VertexShader.h"
#include "Game Engine/Graphics Engine/PixelShader/PixelShader.h"
#include "Game Engine/Graphics Engine/ConstantBuffer/ConstantBuffer.h"

#include <functional>

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	float m_angle;
	Vector3D m_color;
	UINT isRandom;
};


class GameObject
{
	public:
		Transform m_transform;

	public:
		std::string m_name;

	protected:

		VertexBuffer* m_vb;

		VertexShader* m_vs;
		PixelShader* m_ps;

		ConstantBuffer* m_cb;

		

	public:
		Vector3D m_color = Vector3D(1,0,1);
		bool isRainbow = true;
		std::function<void()> doOnUpdate = nullptr;

	public:

		GameObject(std::string name): m_name(name) {}

		virtual bool load() = 0;
		virtual bool release() = 0;

		virtual void Draw() = 0;

		virtual void Update(float delta_time, Matrix4x4 view_matrix, Matrix4x4 projection_matrix) = 0;
};

