#include "SceneTreePanel.h"
#include "TeaEngine/Core/Base.h"
#include "TeaEngine/Scene/Components.h"
#include "TeaEngine/Scene/Entity.h"
#include "TeaEngine/Core/Log.h"
#include "entt/entity/fwd.hpp"
#include <cstdint>
#include <cstring>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <string>


namespace Tea {
    
    SceneTreePanel::SceneTreePanel(const Ref<Scene>& scene)
    {
        m_Context = scene;
    }

    void SceneTreePanel::SetContext(const Ref<Scene>& scene)
    {
        m_Context = scene;
    }

    void SceneTreePanel::OnImGuiRender()
    {
        ImGui::Begin("Scene Tree");
        
        auto view = m_Context->m_Registry.view<entt::entity>();
        for(auto entityID: view)
        {
            Entity entity{ entityID, m_Context.get()};
            DrawEntityNode(entity);
        }

        if(ImGui::IsWindowHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left))
        {
            m_SelectionContext = {};
        }

        ImGui::End();

        ImGui::Begin("Inspector");
        if(m_SelectionContext)
        {
            DrawComponents(m_SelectionContext);
        }

        ImGui::End();
    }

    void SceneTreePanel::DrawEntityNode(Entity entity)
    {
        auto& entityNameTag = entity.GetComponent<TagComponent>().Tag;

        ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, entityNameTag.c_str());

        if(ImGui::IsItemClicked())
        {
            m_SelectionContext = entity;
        }

        if(opened)
        {
            //Here you would call DrawEntityNode for the child nodes and blablabla
            ImGui::TreePop();
        }
    }

    void SceneTreePanel::DrawComponents(Entity entity)
    {
        if(entity.HasComponent<TagComponent>())
        {
            auto& entityNameTag = entity.GetComponent<TagComponent>().Tag;

            ImGui::Text("Tag");
            ImGui::SameLine();

            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy(buffer, entityNameTag.c_str());
            
            if(ImGui::InputText("##", buffer, sizeof(buffer)))
            {
                entityNameTag = std::string(buffer);
            }
        }

        ImGui::Separator();

        if(entity.HasComponent<TransformComponent>())
        {
            auto& transformComponent = entity.GetComponent<TransformComponent>();

            if(ImGui::TreeNode("Transform"))
            {   
                ImGui::Text("Position");
                ImGui::DragFloat3("##Position", glm::value_ptr(transformComponent.Position));
                
                ImGui::Text("Rotation");
                ImGui::DragFloat3("##Rotation", glm::value_ptr(transformComponent.Rotation));

                ImGui::Text("Scale");
                ImGui::DragFloat3("##Scale", glm::value_ptr(transformComponent.Scale));

                ImGui::TreePop();
            }
        }

        ImGui::Separator();

        if(entity.HasComponent<ModelComponent>())
        {
            auto& modelComponent = entity.GetComponent<ModelComponent>();
            if(ImGui::TreeNode("Model"))
            {   
                auto& meshesArray = modelComponent.model->GetMeshes();
                ImGui::SeparatorText("List of Meshes");

                ImGui::Text("Meshes");
                ImGui::SameLine();
                static bool show;
                if(ImGui::Button(("Vector (size " + std::to_string(meshesArray.size()) + ")").c_str()))
                {
                    show = !show;
                }

                if(show)
                {
                    ImGui::BeginListBox("##Test");
                    for (const auto& mesh : meshesArray)
                    {
                        ImGui::Text("Mesh");
                    }
                    ImGui::EndListBox();
                }

                ImGui::TreePop();
            }
        }
    }

}