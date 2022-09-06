//
// Created by ounol on 2022-03-02.
//

#pragma once
#include "MacroDef.h"


class InputMgr {
public:
    DECLARE_SINGLETON(InputMgr);
    ~InputMgr();

    static void CursorPositionCallback(double xpos, double ypos);
    static void SetCanvasSize(int width, int height);

    void Update();
    void LateUpdate();

    bool IsMouseFocus() const {
        return m_focus;
    }

    float GetX() const {
        return m_dx;
    }

    float GetY() const {
        return m_dy;
    }

private:
    float m_x = 0;
    float m_y = 0;
    bool m_focus = false;

    float m_dx = 0;
    float m_dy = 0;

    unsigned int m_width = 0;
    unsigned int m_height = 0;

    float m_halfWidth = 0;
    float m_halfHeight = 0;
};



