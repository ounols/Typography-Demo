//
// Created by ounol on 2022-01-28.
//

#pragma once


#include <Component/SComponent.h>

class RenderOnceComponent : public CSE::SComponent {
public:
    RenderOnceComponent();
    ~RenderOnceComponent() override = default;

    void Init() override;

    void Tick(float elapsedTime) override;

    void Exterminate() override;

private:
    bool m_isRender = false;
};



