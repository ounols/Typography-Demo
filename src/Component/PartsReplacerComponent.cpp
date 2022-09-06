//
// Created by ounol on 2022-01-28.
//

#include "PartsReplacerComponent.h"

#include <Util/Render/SMaterial.h>
#include <Component/RenderComponent.h>
#include <Util/Render/STexture.h>
#include <Util/MoreComponentUtil.h>

using namespace CSE;

COMPONENT_CONSTRUCTOR(PartsReplacerComponent) {

}

void PartsReplacerComponent::Init() {

    const auto& renderComponent = GetRenderComponent(*gameObject);
    m_material = renderComponent->GetMaterial();

    if(!m_url.empty()) SetTexture();
    m_isInit = true;
}

void PartsReplacerComponent::Tick(float elapsedTime) {
    if(!m_isRender) {
        m_isRender = true;
        return;
    }

    SetIsEnable(false);
}

void PartsReplacerComponent::Exterminate() {

}

void PartsReplacerComponent::SetTextureInfo(const std::string& url, const CSE::vec3& color) {
    m_url = url;
    m_color = vec3(color.x, color.y, color.z);
    if (m_isInit) {
        SetTexture();
    }
}

void PartsReplacerComponent::SetTexture() {
#ifndef __EMSCRIPTEN__
    m_texture = SResource::Create<STexture>("file:Texture/" + m_url);
    m_material->SetTexture("texture.albedo", m_texture);
#endif
    m_material->SetVec3("vec3.albedo", m_color);
}
