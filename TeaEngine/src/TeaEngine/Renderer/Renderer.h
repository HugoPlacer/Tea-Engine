#pragma once

#include "TeaEngine/Core/Base.h"
#include "TeaEngine/Renderer/EditorCamera.h"
#include "TeaEngine/Renderer/Framebuffer.h"
#include "TeaEngine/Renderer/Mesh.h"
#include "TeaEngine/Renderer/RendererAPI.h"
#include "TeaEngine/Renderer/Shader.h"
#include "TeaEngine/Renderer/Texture.h"
#include "TeaEngine/Renderer/UniformBuffer.h"
#include "TeaEngine/Renderer/VertexArray.h"
#include "TeaEngine/Scene/Components.h"
#include <glm/fwd.hpp>
#include <vector>

namespace Tea {

    /**
     * @defgroup renderer Renderer
     * @brief Renderer components of the TeaEngine.
     * @{
     */

    /**
     * @brief Structure containing renderer data.
     */
    struct RendererData
    {
        /**
         * @brief Structure containing camera data.
         */
        struct CameraData
        {
            glm::mat4 projection; ///< The projection matrix.
            glm::mat4 view; ///< The view matrix.
            glm::vec3 position; ///< The position of the camera.
        };

        /**
         * @brief Structure containing render data.
         */
        struct RenderData
        {
            LightComponent lights[32]; ///< Array of light components.
            int lightCount = 0; ///< Number of lights.
        };

        CameraData cameraData; ///< Camera data.
        RenderData renderData; ///< Render data.

        Ref<UniformBuffer> CameraUniformBuffer; ///< Uniform buffer for camera data.
        Ref<UniformBuffer> RenderDataUniformBuffer; ///< Uniform buffer for render data.

        Ref<Texture> RenderTexture; ///< Render texture.
    };

    /**
     * @brief Structure containing renderer statistics.
     */
    struct RendererStats
    {
        uint32_t DrawCalls = 0; ///< Number of draw calls.
        uint32_t VertexCount = 0; ///< Number of vertices.
        uint32_t IndexCount = 0; ///< Number of indices.
    };

    /**
     * @brief Structure containing render settings.
     */
    struct RenderSettings
    {
        bool PostProcessing = true; ///< Enable or disable post-processing.
        bool SSAO = false; ///< Enable or disable SSAO.
        bool Bloom = false; ///< Enable or disable bloom.
        bool FXAA = false; ///< Enable or disable FXAA.
        float Exposure = 1.0f; ///< Exposure value.
    };

    /**
     * @brief Class representing the 3D renderer.
     */
    class Renderer
    {
    public:
        /**
         * @brief Initializes the renderer.
         */
        static void Init();

        /**
         * @brief Shuts down the renderer.
         */
        static void Shutdown();

        /**
         * @brief Begins a new scene with the specified editor camera.
         * @param camera The editor camera.
         */
        static void BeginScene(EditorCamera& camera);

        /**
         * @brief Begins a new scene with the specified camera and transform.
         * @param camera The camera.
         * @param transform The transform matrix.
         */
        static void BeginScene(const Camera& camera, const glm::mat4& transform);

        /**
         * @brief Ends the current scene.
         */
        static void EndScene();

        /**
         * @brief Begins an overlay with the specified editor camera.
         * @param camera The editor camera.
         */
        static void BeginOverlay(EditorCamera& camera);

        /**
         * @brief Ends the current overlay.
         */
        static void EndOverlay();

        /**
         * @brief Submits a draw call with the specified shader, vertex array, and transform.
         * @param shader The shader.
         * @param vertexArray The vertex array.
         * @param transform The transform matrix.
         */
        static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

        /**
         * @brief Submits a draw call with the specified material, mesh, and transform.
         * @param material The material.
         * @param mesh The mesh.
         * @param transform The transform matrix.
         */
        static void Submit(const Ref<Material>& material, const Ref<Mesh>& mesh, const glm::mat4& transform = glm::mat4(1.0f));

        /**
         * @brief Submits a light component.
         * @param light The light component.
         */
        static void Submit(const LightComponent& light);

        /**
         * @brief Resizes the renderer to the specified width and height.
         * @param width The new width.
         * @param height The new height.
         */
        static void OnResize(uint32_t width, uint32_t height);

        /**
         * @brief Gets the render texture.
         * @return A reference to the render texture.
         */
        static const Ref<Texture>& GetRenderTexture() { return s_RendererData.RenderTexture; }

        /**
         * @brief Gets the renderer data.
         * @return A reference to the renderer data.
         */
        static const RendererData& GetData() { return s_RendererData; }

        /**
         * @brief Gets the renderer statistics.
         * @return A reference to the renderer statistics.
         */
        static const RendererStats& GetStats() { return s_Stats; }

        /**
         * @brief Gets the render settings.
         * @return A reference to the render settings.
         */
        static RenderSettings& GetRenderSettings() { return s_RenderSettings; }

    private:
        static RendererData s_RendererData; ///< Renderer data.
        static RendererStats s_Stats; ///< Renderer statistics.
        static RenderSettings s_RenderSettings; ///< Render settings.

        static Ref<Texture> s_MainRenderTexture; ///< Main render texture.
        static Ref<Texture> s_PostProcessingTexture; ///< Post-processing texture.
        static Ref<Texture> s_DepthTexture; ///< Depth texture.

        static Ref<Framebuffer> s_MainFramebuffer; ///< Main framebuffer.
        static Ref<Framebuffer> s_PostProcessingFramebuffer; ///< Post-processing framebuffer.

        static Ref<Mesh> s_ScreenQuad; ///< Screen quad mesh.

        static Ref<Shader> s_ToneMappingShader; ///< Tone mapping shader.
        static Ref<Shader> s_FinalPassShader; ///< Final pass shader.
    };

    /** @} */
}