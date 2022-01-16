#pragma once

namespace Pineapple
{

template <typename T> class Image
{
public:
    Image() = default;

    Image(const uint32_t width, const uint32_t height, const uint32_t channels)
        : m_Buffer(width * height * channels), m_Width(width), m_Height(height),
          m_Channels(channels)
    {
    }

    Image(const std::vector<T>& data, const uint32_t width,
        const uint32_t height, const uint32_t channels)
        : m_Buffer(data), m_Width(width), m_Height(height), m_Channels(channels)
    {
    }

    Image(const T* ptr, const uint32_t width, const uint32_t height,
        const uint32_t channels)
        : m_Width(width), m_Height(height), m_Channels(channels)
    {
        m_Buffer.assign(ptr, ptr + width * height * channels);
    }

    Image(const Image<T>& other) = default;
    Image(Image<T>&& other) = default;
    ~Image() = default;

    Image<T>& operator=(const Image<T>& other) = default;
    Image<T>& operator=(Image<T>&& other) = default;

    inline std::vector<T>& GetBuffer() { return m_Buffer; }
    inline const std::vector<T>& GetBuffer() const { return m_Buffer; }

    inline T* GetPtr() { return m_Buffer.data(); }
    inline const T* GetPtr() const { return m_Buffer.data(); }

    inline uint32_t GetWidth() const { return m_Width; }
    inline uint32_t GetHeight() const { return m_Height; }
    inline uint32_t GetChannels() const { return m_Channels; }
    inline uint32_t GetSize() const { return m_Buffer.size(); }

    std::string ToString() const
    {
        std::stringstream ss;
        ss << "Image: " << static_cast<const void*>(GetPtr()) << ", "
           << GetSize() << " (" << GetWidth() << "," << GetHeight() << ","
           << GetChannels() << ")";
        return ss.str();
    }

    friend std::ostream& operator<<(std::ostream& os, const Image& image)
    {
        return os << image.ToString();
    }

private:
    std::vector<T> m_Buffer;
    uint32_t m_Width;
    uint32_t m_Height;
    uint32_t m_Channels;
};

} // namespace Pineapple
