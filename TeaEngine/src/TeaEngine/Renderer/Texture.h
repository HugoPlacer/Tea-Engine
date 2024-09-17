#pragma once

#include "TeaEngine/Core/Base.h"
#include "TeaEngine/IO/Resource.h"
#include "TeaEngine/Renderer/Image.h"

#include <cstdint>
#include <string>
#include <unordered_map>

namespace Tea {

    enum class ImageFormat
    {
        //Color
        R8,
        RG8,
        RGB8,
        SRGB8,
        RGBA8,
        SRGBA8,
        RGBA32F,


        //Depth
        DEPTH24STENCIL8
    };

    struct TextureProperties
    {
        ImageFormat Format;
        uint32_t Width, Height;
        bool GenerateMipmaps = true;
        bool srgb = true;
    };

    class Texture : public Resource
    {
    public:
        Texture(const TextureProperties& properties);
        Texture(uint32_t width, uint32_t height, ImageFormat imageFormat);
        Texture(const std::filesystem::path& path, bool srgb = true);
        ~Texture();

        void Bind(uint32_t slot);

        void Resize(uint32_t width, uint32_t height);

        std::pair<uint32_t, uint32_t> GetSize() { return std::make_pair(m_Width, m_Height); };
        uint32_t GetWidth() { return m_Width; };
        uint32_t GetHeight() { return m_Width; };
        uint32_t GetID() { return m_textureID; };

        void SetData(void* data, uint32_t size);
        ImageFormat GetImageFormat() { return m_Properties.Format; };

        static Ref<Texture> Load(const std::filesystem::path& path, bool srgb = true);
        static Ref<Texture> Create(uint32_t width, uint32_t height, ImageFormat format);
    private:
        TextureProperties m_Properties;

        uint32_t m_textureID;
        int m_Width, m_Height;
    };
}
