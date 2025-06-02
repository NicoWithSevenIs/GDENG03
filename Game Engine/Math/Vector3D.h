#pragma once

class Vector3D {

	public:
		float m_x, m_y, m_z;

	public:
		Vector3D(): m_x(0), m_y(0), m_z(0) {}
		Vector3D(float x, float  y, float  z) : m_x(x), m_y(y), m_z(z) {}
		Vector3D(const Vector3D& v): m_x(v.m_x), m_y(v.m_y), m_z(v.m_z){}
		~Vector3D(){}


		static Vector3D lerp(const Vector3D& start, const Vector3D& end, float t) 
		{
			Vector3D v;

			v.m_x = start.m_x * (1.f-t) + end.m_x * t; 
			v.m_y = start.m_y * (1.f - t) + end.m_y * t;
			v.m_z = start.m_z * (1.f - t) + end.m_z * t;


			return v;
		}

};