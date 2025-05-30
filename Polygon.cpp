#include "Polygon.h"
#include <Windows.h>
#include "Game Engine/Graphics Engine/GraphicsEngine.h"
#include "Game Engine/Graphics Engine/DeviceContext/DeviceContext.h"

using namespace Nico;

Polygon::Polygon()
{
}

Polygon::~Polygon()
{
}


bool Polygon::init(std::vector<vertex> vertices)
{
    this->m_vb = GraphicsEngine::get()->createVertexBuffer();
    this->m_vertices = vertices;
    return true;
}

bool Polygon::release()
{
    this->m_vb->release();
    delete this;
    return true;
}

void Nico::Polygon::draw()
{
    GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->m_vb);
    GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(this->m_vb->getSizeVertexList(), 0);
}

bool Polygon::load(void* shader_byte_code, size_t size_shader)
{
    UINT size_list = this->m_vertices.size();
    this->m_vb->load(this->m_vertices.data(), sizeof(vertex), size_list, shader_byte_code, size_shader);
    return true;
}
