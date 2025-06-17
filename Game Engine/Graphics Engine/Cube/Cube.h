#pragma once


#include <vector>

#include "../../../GameObject.h"


class Cube: public GameObject {
	

	public:
		IndexBuffer* m_ib;

		std::vector<vertex> cube_list;
		std::vector<unsigned int> index_list;

		float pace = 0.1f;
		float dir = 1.f;

	public:
		Cube();
		Cube(std::string name);

		bool load() override;
		bool release() override;
		void Update(float delta_time, Matrix4x4 view_matrix, Matrix4x4 projection_matrix) override;
		void Draw() override;
		
};

