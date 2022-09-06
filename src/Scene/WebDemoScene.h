#pragma once
#include "Manager/Base/Scene.h"
#include "Object/SGameObject.h"
#include "Util/Render/MeshSurface.h"

namespace CSE {
    class SPrefab;
}
class RenderOnceComponent;

class WebDemoScene : public CSE::Scene {
public:
    WebDemoScene() = default;
    ~WebDemoScene() override = default;

    void Init() override;
    void Tick(float elapsedTime) override;
    void Destroy() override;

private:
    CSE::SGameObject*
    CreateCharacterParts(CSE::SPrefab* plane, const std::string& url, CSE::SGameObject& root, CSE::vec3 color);

private:
    RenderOnceComponent* m_renderOnceComponent = nullptr;
    short m_partsSize = 0;
};
