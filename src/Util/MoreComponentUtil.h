#pragma once

#include <Component/SComponent.h>

namespace CSE {
    class RenderComponent;
}

static CSE::RenderComponent* GetRenderComponent(const CSE::SGameObject& object) {
    const auto& children = object.GetChildren();
    for (const auto& gameObject : children) {
        const auto& component = gameObject->GetComponent<CSE::RenderComponent>();
        if(component == nullptr) {
            const auto& result = GetRenderComponent(*gameObject);
            if(result != nullptr) return result;
        }
        return component;
    }
    return nullptr;
}
