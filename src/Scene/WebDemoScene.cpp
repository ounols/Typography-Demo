#include "WebDemoScene.h"
#include <sstream>
#include <random>

#include "Util/Render/SEnvironmentMgr.h"
#include "Component/LightComponent.h"
#include "Component/CameraComponent.h"
#include "Component/RenderComponent.h"
#include <Util/MoreComponentUtil.h>
#include <Component/PartsReplacerComponent.h>
#include <Component/RenderOnceComponent.h>
#include <Component/CustomComponent.h>
#include <Component/ObjectMovementComponent.h>

#include "Util/Loader/DAE/DAELoader.h"
#include "Util/Render/SFrameBuffer.h"
#include "Util/Render/SMaterial.h"
using namespace CSE;

void WebDemoScene::Init() {
    auto root = new SGameObject("root");

    /// Plane Prefab
    auto circlePlanePrefab = SResource::Create<SPrefab>("plane_circle.prefab");
    const auto& planePrefabRenderComp = GetRenderComponent(*circlePlanePrefab->GetRoot());
    planePrefabRenderComp->SetMaterial(SResource::Create<SMaterial>("file:Material/Character.mat"));

    // Result Render
    SGameObject* plane = circlePlanePrefab->Clone(vec3{ 0, 0, 0 }, root);
    plane->GetTransform()->m_scale = vec3{ 0.5f, 0.5f, 0.5f };
    plane->GetTransform()->m_rotation = Quaternion::AngleAxis(vec3{ 0, 0, 1 }, Pi);
    const auto& currentPlaneRenderComponent = GetRenderComponent(*plane);
    currentPlaneRenderComponent->SetMaterial(SResource::Create<SMaterial>("file:Material/Card.mat"));
//    const auto& script = plane->CreateComponent<CustomComponent>();
//    script->SetClassName("Stormtrooper.script");
    plane->CreateComponent<ObjectMovementComponent>();

    // Main Camera
    auto camera = new SGameObject("camera");
    camera->CreateComponent<CameraComponent>();
    camera->GetTransform()->m_position = vec3{ 0, 0, 1.5f };

    // Directional Light
    SGameObject* direction = new SGameObject();
    direction->SetParent(root);
    direction->SetName("directional");
    direction->GetTransform()->m_position = vec3{ 0.f, 0.5f, 0.f };
    direction->CreateComponent<LightComponent>();
    direction->GetComponent<LightComponent>()->SetSunrising(true);
    direction->GetComponent<LightComponent>()->SetLightType(LightComponent::DIRECTIONAL);
    direction->GetComponent<LightComponent>()->SetDirection(vec4{ 0.0f, 1.0f, 1, 0 });
    direction->GetComponent<LightComponent>()->SetShadow(true);

    // Character Render Root
    auto characterRoot = new SGameObject("character root");
    // Camera for Character Framebuffer
    auto characterCameraObj = new SGameObject("character camera");
    characterCameraObj->SetParent(characterRoot);
    m_renderOnceComponent = characterCameraObj->CreateComponent<RenderOnceComponent>();
    m_renderOnceComponent->SetIsEnable(false);
    const auto& charCamera = characterCameraObj->CreateComponent<CameraComponent>();
    characterCameraObj->GetTransform()->m_position = vec3{ 0, 0, 1.2f };
    charCamera->SetFrameBuffer(SResource::Create<SFrameBuffer>("File:Texture/CharacterCamera.framebuffer"));

    // Random for Colors
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.1f, 0.9f);
    const auto hairColor = vec3{ dis(gen), dis(gen), dis(gen) };
    const auto eyesColor = vec3{ dis(gen), dis(gen), dis(gen) };

    // Character Parts
    CreateCharacterParts(circlePlanePrefab, "back_hair_fill_0.png", *characterRoot, hairColor * 0.6f);
    CreateCharacterParts(circlePlanePrefab, "static_face_fill_0.png", *characterRoot, vec3{ 1, 0.9764f, 0.9215f });
    CreateCharacterParts(circlePlanePrefab, "front_hair_fill_0.png", *characterRoot, hairColor);
    CreateCharacterParts(circlePlanePrefab, "static_body_base_0.png", *characterRoot, vec3{ 1, 1, 1 });

    CreateCharacterParts(circlePlanePrefab, "eyebrow_fill_0.png", *characterRoot, hairColor * 0.6f);
    CreateCharacterParts(circlePlanePrefab, "left_eye_base_0.png", *characterRoot, vec3{ 1, 1, 1 });
    CreateCharacterParts(circlePlanePrefab, "left_eye_fill_0.png", *characterRoot, eyesColor);
    CreateCharacterParts(circlePlanePrefab, "left_eye_draw_0.png", *characterRoot, vec3{ 1, 1, 1 });
    CreateCharacterParts(circlePlanePrefab, "right_eye_base_0.png", *characterRoot, vec3{ 1, 1, 1 });
    CreateCharacterParts(circlePlanePrefab, "right_eye_fill_0.png", *characterRoot, eyesColor);
    CreateCharacterParts(circlePlanePrefab, "right_eye_draw_0.png", *characterRoot, vec3{ 1, 1, 1 });
    CreateCharacterParts(circlePlanePrefab, "mouth_base_0.png", *characterRoot, vec3{ 1, 1, 1 });

    characterRoot->GetTransform()->m_position = vec3{ -100.f, 100.f, 0 };

    // GL Config
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
}

void WebDemoScene::Tick(float elapsedTime) {
    // 현재 레거시 모드로 돌리기 때문에 모든 오브젝트들은 엔진 코어에서 업데이트 됩니다.
    // 따라서 이 곳에 작성할 코드는 없습니다! 예외 상황일 때 사용해도 무방한 함수입니다.
}

void WebDemoScene::Destroy() {
    // 현재 레거시 모드로 돌리기 때문에 모든 오브젝트들은 엔진이 끝날 때 다같이 소멸됩니다.
    // 따라서 이 곳에 작성할 코드는 없습니다! 예외 상황일 때 사용해도 무방한 함수입니다.
}

CSE::SGameObject* WebDemoScene::CreateCharacterParts(CSE::SPrefab* plane, const std::string& url,
                                                     CSE::SGameObject& root, CSE::vec3 color) {
    SGameObject* gameObject = plane->Clone(vec3{ 0, 0, 0.001f * m_partsSize }, &root);
    gameObject->GetTransform()->m_scale = vec3{ 0.5f, 0.5f, 0.5f };
    const auto& partsComponent = gameObject->CreateComponent<PartsReplacerComponent>();
#ifdef __EMSCRIPTEN__
    const auto& bindTexture = gameObject->CreateComponent<BindTexSampleComponent>();
    const auto textureName = "parts_" + std::to_string(m_partsSize);
    bindTexture->SetTexture("https://moyodao.net/imgTest/" + url, textureName);
    partsComponent->SetTextureInfo(textureName, color);
#else
    partsComponent->SetTextureInfo(url, color);
#endif

    ++m_partsSize;

    return gameObject;
}