#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
public:
    Camera();
    Camera(std::string name);

    bool load() override;
    bool release() override;
    void Draw() override;
    void Update(float delta_time, Matrix4x4 view_matrix, Matrix4x4 projection_matrix) override;

    void setSubject(GameObject* subject);
    void setOrbitParams(float radius, float height, float speed);

    Matrix4x4 getViewMatrix() const;
    Matrix4x4 getProjectionMatrix() const;

private:
    GameObject* m_subject = nullptr;
    float m_orbit_radius = 10.0f;
    float m_orbit_height = 5.0f;
    float m_orbit_speed = 1.0f;
    float m_angle = 0.0f;

    Matrix4x4 m_view_matrix;
    Matrix4x4 m_projection_matrix;
};
