#include "Camera.h"
#include <cmath>

Camera::Camera() : GameObject("Camera") {}

Camera::Camera(std::string name) : GameObject(name)
{
}

bool Camera::load()
{
    return true;
}

bool Camera::release()
{
    return true;
}

void Camera::Draw()
{
}

void Camera::Update(float delta_time, Matrix4x4, Matrix4x4)
{
    if (m_subject)
    {
        m_angle += delta_time * m_orbit_speed;

        float x = std::cos(m_angle) * m_orbit_radius;
        float z = std::sin(m_angle) * m_orbit_radius;
        float y = m_orbit_height;

        Vector3D subject_pos = m_subject->m_transform.getTransform();
        m_transform.setTransform(Vector3D(x, y, z) + subject_pos);
        m_transform.lookAt(subject_pos);
    }

    m_view_matrix.SetIdentity();
    m_transform.GetTransformationMatrix().inverse();

    float aspectRatio = 16.0f / 9.0f;
    m_projection_matrix.setPerspectiveFovLH(1.57f, aspectRatio, 0.1f, 1000.0f);

    if (doOnUpdate)
        doOnUpdate();
}

void Camera::setSubject(GameObject* subject)
{
    m_subject = subject;
}

void Camera::setOrbitParams(float radius, float height, float speed)
{
    m_orbit_radius = radius;
    m_orbit_height = height;
    m_orbit_speed = speed;
}

Matrix4x4 Camera::getViewMatrix() const
{
    return m_view_matrix;
}

Matrix4x4 Camera::getProjectionMatrix() const
{
    return m_projection_matrix;
}
