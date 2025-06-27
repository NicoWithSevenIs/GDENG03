#pragma once

#include "Game Engine/Math/Matrix4x4.h"
#include "Game Engine/Graphics Engine/Transform/Transform.h"



class Camera {

	public:
		Transform m_transform;

	public:
		//virtual void GetViewProjMat(Matrix4x4* view_matrix, Matrix4x4** proj_matrix) = 0;
		inline virtual Matrix4x4 GetViewMatrix() {
			Matrix4x4 mat = Matrix4x4(this->m_transform.GetTransformationMatrix());
			mat.inverse();
			return mat;
		}
		virtual Matrix4x4 GetProjectionMatrix() = 0;
		virtual void Update() = 0;
};

/*
projection_matrix.setOrthoLH(
	(rc.right - rc.left) / 400.f,
	(rc.bottom - rc.top) / 400.f,
	-4.f,
	4.f
);
*/
