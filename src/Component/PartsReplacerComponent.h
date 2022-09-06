#pragma once

#include <Component/SComponent.h>

namespace CSE {
    class STexture;
    class SMaterial;
}

class PartsReplacerComponent : public CSE::SComponent {
public:
    PartsReplacerComponent();
    ~PartsReplacerComponent() override = default;

    void Init() override;

    void Tick(float elapsedTime) override;

    void Exterminate() override;

    void SetTextureInfo(const std::string& url, const CSE::vec3 &color);

private:
    void SetTexture();

private:
    std::string m_url;
    CSE::vec3 m_color;
    CSE::STexture* m_texture = nullptr;
    CSE::SMaterial* m_material = nullptr;

    bool m_isInit = false;
    bool m_isRender = false;
};



