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
    RenderOnceComponent* m_renderOnceComponent = nullptr;
    short m_partsSize = 0;
};
