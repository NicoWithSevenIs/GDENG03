#pragma once
#include <memory>
#include "Vector3D.h"

class Matrix4x4 {

public:
	float m_mat[4][4] = {};

public:
	Matrix4x4(){
		SetIdentity();
	}

	~Matrix4x4() {}
	
	void SetIdentity() 
	{
		::memset(m_mat, 0, sizeof(float) * 16);
		for (int i = 0; i < 4; i++) 
			m_mat[i][i] = 1;	
	}

	void SetTranslation(const Vector3D& translation) 
	{
		SetIdentity();
		m_mat[3][0] = translation.m_x;
		m_mat[3][1] = translation.m_y;
		m_mat[3][2] = translation.m_z;
	}

	void SetScale(const Vector3D& scale) {
		SetIdentity();
		m_mat[0][0] = scale.m_x;
		m_mat[1][1] = scale.m_y;
		m_mat[2][2] = scale.m_z;
	}

	void setOrthoLH(float width, float height, float near_plane, float far_plane) 
	{
		SetIdentity();
		m_mat[0][0] = 2.f / width;
		m_mat[1][1] = 2.f / height;
		m_mat[2][2] = 1.f / (far_plane - near_plane);
		m_mat[3][2] = -(near_plane / (far_plane - near_plane));
	}

	void setRotationX(float x)
	{
		m_mat[1][1] = cos(x);
		m_mat[1][2] = -sin(x);
		m_mat[2][1] = sin(x);
		m_mat[2][2] = cos(x);
	}

	void setRotationY(float y)
	{
		m_mat[0][0] = cos(y);
		m_mat[0][2] = sin(y);
		m_mat[2][0] = -sin(y);
		m_mat[2][2] = cos(y);
	}

	void setRotationZ(float z)
	{
		m_mat[0][0] = cos(z);
		m_mat[0][1] = -sin(z);
		m_mat[1][0] = sin(z);
		m_mat[1][1] = cos(z);
	}

	void operator *= (const Matrix4x4& mat) 
	{
		Matrix4x4 out;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				
				out.m_mat[i][j] =
					m_mat[i][0] * mat.m_mat[0][j] + m_mat[i][1] * mat.m_mat[1][j] + 
					m_mat[i][2] * mat.m_mat[2][j] + m_mat[i][3] * mat.m_mat[3][j];

			}
		}

		::memcpy(m_mat, out.m_mat, sizeof(float) * 16);
	}


};