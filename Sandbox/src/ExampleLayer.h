#pragma once

#include "TeaEngine/Renderer/Camera.h"
#include "TeaEngine/Renderer/EditorCamera.h"
#include "TeaEngine/Renderer/Model.h"
#include <TeaEngine/Renderer/RendererAPI.h>
#include <TeaEngine/Renderer/Shader.h>
#include <TeaEngine/Renderer/Texture.h>
#include <TeaEngine/Core/Layer.h>

class ExampleLayer : public Tea::Layer
{
public:
    ExampleLayer();

    void OnUpdate(float dt) override;

    void OnEvent(Tea::Event& event);

    void OnImGuiRender();
private:
    Tea::Ref<Tea::VertexArray> m_VertexArray;
    Tea::Ref<Tea::VertexBuffer> m_VertexBuffer;
    Tea::Ref<Tea::IndexBuffer> m_IndexBuffer;
    Tea::Scope<Tea::RendererAPI> m_RendererAPI;

    Tea::Ref<Tea::Shader> m_defaultShader;
    Tea::Ref<Tea::Texture> m_Texture;

    Tea::Model helmet;
    Tea::Model plane;

    Tea::EditorCamera m_EditorCamera;

};
