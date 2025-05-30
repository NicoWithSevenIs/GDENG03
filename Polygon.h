#pragma once
#include "Game Engine/Graphics Engine/VertexBuffer/VertexBuffer.h"
#include <vector>

struct vec3 {
	float x, y, z;
};

struct vertex {
	vec3 position;
	vec3 color;
};

namespace Nico {

	class Polygon
	{
	private:
		std::vector<vertex> m_vertices;
		VertexBuffer* m_vb;

	public:
		Polygon();
		~Polygon();

		bool init(std::vector<vertex> vertices);
		bool load(void* shader_byte_code, size_t size_shader);
		bool release();
		void draw();

	};


}
