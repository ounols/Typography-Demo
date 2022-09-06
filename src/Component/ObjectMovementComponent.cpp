#include "../Manager/InputMgr.h"
#include "ObjectMovementComponent.h"

using namespace CSE;

COMPONENT_CONSTRUCTOR(ObjectMovementComponent) {
}

void ObjectMovementComponent::Init() {
    m_input = InputMgr::getInstance();
}

void ObjectMovementComponent::Tick(float elapsedTime) {
    if(!m_input->IsMouseFocus()) return;

    m_currentX += (m_input->GetX() - m_currentX) * m_speed;
    m_currentY += (m_input->GetY() - m_currentY) * m_speed;

    gameObject->GetTransform()->m_rotation = flip.Rotated(Quaternion::AngleAxis(vec3{m_currentY, m_currentX, 0}, -0.5f));
}

void ObjectMovementComponent::Exterminate() {

}
