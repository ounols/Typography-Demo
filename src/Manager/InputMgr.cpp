//
// Created by ounol on 2022-03-02.
//

#include <string>
#include "InputMgr.h"

IMPLEMENT_SINGLETON(InputMgr);

InputMgr::InputMgr() {

}

InputMgr::~InputMgr() {

}

void InputMgr::CursorPositionCallback(double xpos, double ypos) {
    const auto& instance = InputMgr::getInstance();
    instance->m_x = xpos;
    instance->m_y = ypos;
    instance->m_focus = true;
}

void InputMgr::Update() {
    m_dx = (m_x - static_cast<float>(m_width) * 0.5f) / m_halfWidth;
    m_dy = (m_y - static_cast<float>(m_height) * 0.5f) / m_halfHeight;
}

void InputMgr::LateUpdate() {
    m_focus = false;
}

void InputMgr::SetCanvasSize(int width, int height) {
    const auto& instance = InputMgr::getInstance();
    instance->m_width = width;
    instance->m_height = height;
    instance->m_halfWidth = width / 2.f;
    instance->m_halfHeight = height / 2.f;
}
