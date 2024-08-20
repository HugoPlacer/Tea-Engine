#pragma once

#include "TeaEngine/Core/Base.h"
#include "TeaEngine/Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace Tea {

    class RendererAPI{
    public:

        static void Init();

        static void SetClearColor(const glm::vec4& color);
        static void Clear();

        static void SetDepthMask(bool enabled);

        static void DrawIndexed(const Ref<VertexArray>& vertexArray);

        static void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount, float lineWidth = 1.0f);

        static Scope<RendererAPI> Create();

        private:
        static Scope<RendererAPI> s_RendererAPI;
    };

};