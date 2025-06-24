#pragma once

#include "../../Math/Vector3D.h"
#include "../../Math/Matrix4x4.h"

class Transform
{
public:
	Vector3D m_translation;
	Vector3D m_scale;
	Vector3D m_rotation;

private:
	Matrix4x4 m_transformation_matrix;

public:
	Transform() : m_translation(Vector3D()), m_scale(Vector3D(1, 1, 1)), m_rotation(Vector3D()) {}

	void BuildTransform()
	{
		Matrix4x4 m;
		m.SetIdentity();

		Matrix4x4 sm;
		sm.SetScale(m_scale);
		m *= sm;

		Matrix4x4 rm;
		rm.SetIdentity();
		rm.setRotationX(m_rotation.m_x);
		m *= rm;

		rm.SetIdentity();
		rm.setRotationY(m_rotation.m_y);
		m *= rm;

		rm.SetIdentity();
		rm.setRotationZ(m_rotation.m_z);
		m *= rm;

		Matrix4x4 tm;
		tm.SetTranslation(m_translation);
		m *= tm;

		this->m_transformation_matrix = m;
	}

	Matrix4x4 GetTransformationMatrix()
	{
		BuildTransform();
		return m_transformation_matrix;
	}

	void lookAt(const Vector3D& target)
	{
		Vector3D direction;
		direction.normalize((target - m_translation));
		float yaw = std::atan2(direction.m_x, direction.m_z);
		float pitch = std::asin(-direction.m_y);

		m_rotation.m_y = yaw;
		m_rotation.m_x = pitch;
	}

	Vector3D getTransform() const
	{
		return m_translation;
	}

	void setTransform(const Vector3D& position)
	{
		m_translation = position;
	}
};
