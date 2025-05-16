#pragma once

class VertexBuffer {
	public:
		VertexBuffer();
		~VertexBuffer();

		bool load();
		bool release();
};