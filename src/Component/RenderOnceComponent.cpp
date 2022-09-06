//
// Created by ounol on 2022-01-28.
//

#include <Util/SafeLog.h>
#include "RenderOnceComponent.h"

using namespace CSE;

COMPONENT_CONSTRUCTOR(RenderOnceComponent) {

}

void RenderOnceComponent::Init() {

}

void RenderOnceComponent::Tick(float elapsedTime) {
    if(!m_isRender) {
        m_isRender = true;
        return;
    }

    gameObject->SetIsEnable(false);
    SafeLog::Log("Rendering Closed.");
}

void RenderOnceComponent::Exterminate() {

}
