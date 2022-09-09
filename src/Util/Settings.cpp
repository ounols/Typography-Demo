//
// Created by ounol on 2021-08-14.
//

#include "Settings.h"

using namespace CSE;

const char* Settings::m_deferredGeometryPassShaderID = "File:Shader/PBR/PBR-Geometry-Pass.shader";
const char* Settings::m_defaultForwardMaterialID = "File:Material/DefaultPBR.mat";
const char* Settings::m_defaultDeferredMaterialID = "File:Material/Default.mat";
const char* Settings::m_defaultDeferredProxyMaterialID = "File:Material/DefaultPBR.mat";
const char* Settings::m_defaultMainBufferShaderID = "File:Shader/Main-Buffer.shader";
const char* Settings::m_defaultBlitBufferShaderID = "File:Shader/Blit-Buffer.shader";
const int Settings::m_maxLights = 1;

// 에셋 폴더를 불러오는거면 false
// 에셋 zip파일을 불러오는거면 true로 맞춰주시면 됩니다.
// 대신 커밋 시 해당 파일 내 __EMSCRIPTEN__ 값이 Settings::m_assetsPacked = true 로 되어있어야 웹에서 정상작동 합니다!
#if defined(_WIN32) || defined(__APPLE_CC__)
const bool Settings::m_assetsPacked = false;
#elif __EMSCRIPTEN__
const bool Settings::m_assetsPacked = true;
#endif

const int Settings::m_maxJoints = 20;

Settings::Settings() = default;

Settings::~Settings() = default;

const char* Settings::GetDeferredGeometryPassShaderID() {
    return m_deferredGeometryPassShaderID;
}

const char* Settings::GetDefaultForwardMaterialId() {
    return m_defaultForwardMaterialID;
}

const char* Settings::GetDefaultDeferredMaterialId() {
    // 포워드 렌더링만 적용되도록 설정합니다.
    // 디퍼드 렌더링으로 설정되어있어도 해당 코드 떄문에 포워드로 동작하게 됩니다.
    return m_defaultDeferredProxyMaterialID;

    return m_defaultDeferredMaterialID;
}

const char* Settings::GetDefaultMainBufferShaderID() {
    return m_defaultMainBufferShaderID;
}

const char* Settings::GetDefaultBlitBufferShaderID() {
    return m_defaultBlitBufferShaderID;
}

int Settings::GetMaxLights() {
    return m_maxLights;
}

int Settings::GetMaxJoints() {
    return m_maxJoints;
}