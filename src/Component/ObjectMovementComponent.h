#pragma once

#include <Component/SComponent.h>

class InputMgr;

class ObjectMovementComponent : public CSE::SComponent {
public:
    ObjectMovementComponent();
    ~ObjectMovementComponent() override = default;

    void Init() override;

    void Tick(float elapsedTime) override;

    void Exterminate() override;

private:
    float m_speed = 0.2f;

    float m_currentX = 0;
    float m_currentY = 0;

    InputMgr* m_input = nullptr;
    const CSE::Quaternion flip = CSE::Quaternion::AngleAxis(CSE::vec3{ 0, 0, 1 }, CSE::Pi);
};

