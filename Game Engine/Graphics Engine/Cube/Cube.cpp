#include "Cube.h"
#include "../GraphicsEngine.h"
#include "../DeviceContext/DeviceContext.h"

Cube::Cube() :m_transform(Matrix4x4()), m_name("Cube") {}

Cube::Cube(std::string name):m_transform(Matrix4x4()), m_name(name) {}

bool Cube::load()
{
	vertex cube_list[] = {
			{Vector3D(-0.5f, -0.5f, -0.5f), Vector3D(0, 1, 0), Vector3D(1, 0, 0)},
			{Vector3D(-0.5f,  0.5f, -0.5f), Vector3D(1, 0, 1), Vector3D(0, 0, 1)},
			{Vector3D(0.5f,  0.5f, -0.5f), Vector3D(0, 0, 1), Vector3D(1, 1, 0)},
			{Vector3D(0.5f, -0.5f, -0.5f), Vector3D(1, 1, 1), Vector3D(0, 1, 1)},
			{Vector3D(0.5f, -0.5f,  0.5f), Vector3D(0, 1, 0), Vector3D(1, 0, 1)},
			{Vector3D(0.5f,  0.5f,  0.5f), Vector3D(1, 0, 0), Vector3D(1, 1, 1)},
			{Vector3D(-0.5f,  0.5f,  0.5f), Vector3D(0, 0, 1), Vector3D(0, 1, 0)},
			{Vector3D(-0.5f, -0.5f,  0.5f), Vector3D(1, 1, 0), Vector3D(0, 0, 0)},
	};

	unsigned int index_list[] =
	{
		// FRONT SIDE
		0, 1, 2,   // FIRST TRIANGLE
		2, 3, 0,   // SECOND TRIANGLE

		// BACK SIDE
		4, 5, 6,
		6, 7, 4,

		// TOP SIDE
		1, 6, 5,
		5, 2, 1,

		// BOTTOM SIDE
		7, 0, 3,
		3, 4, 7,

		// RIGHT SIDE
		3, 2, 5,
		5, 4, 3,

		// LEFT SIDE
		7, 6, 1,
		1, 0, 7
	};



	this->m_vb = GraphicsEngine::get()->createVertexBuffer();
	this->m_ib = GraphicsEngine::get()->createIndexBuffer();

	UINT size_list = ARRAYSIZE(cube_list);
	UINT size_index_list = ARRAYSIZE(index_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	this->m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	this->m_vb->load(cube_list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	this->m_ib->load(index_list, size_index_list);

	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	this->m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();


	constant cc;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

	m_transform.SetTranslation(Vector3D());


	return true;
}

bool Cube::release()
{
	this->m_ib->release();
	this->m_vb->release();
	this->m_vs->release();
	this->m_ps->release();
	this->m_cb->release();
	delete this;
	return true;
}

void Cube::Draw()
{
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(this->m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(this->m_ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedList(m_ib->getSizeIndexList(), 0, 0);
}

void Cube::Update(float delta_time, RECT client_rect)
{
	
	constant cc;

	m_x_rot += delta_time;
	m_y_rot += delta_time;





	cc.m_angle = delta_time;


	cc.m_world = this->m_transform;

	cc.m_view.SetIdentity();
	cc.m_proj.setOrthoLH(
		(client_rect.right - client_rect.left) / 400.f,
		(client_rect.bottom - client_rect.top) / 400.f,
		-4.f,
		4.f
	);

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(this->m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(this->m_ps, m_cb);

}
