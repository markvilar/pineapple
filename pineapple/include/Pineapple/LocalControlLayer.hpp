#pragma once

#include <Pine/Pine.hpp>

#include "Pineapple/CameraControls.hpp"
#include "Pineapple/RecordManager.hpp"
#include "Pineapple/SensorData.hpp"
#include "Pineapple/UserInterface.hpp"
#include "Pineapple/Utils.hpp"

namespace Pineapple
{

class LocalControlLayer : public Pine::Layer
{
public:
    LocalControlLayer();
    ~LocalControlLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Pine::Timestep ts) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Pine::Event& e) override;

private:
    void UpdatePanelLayouts();

private:
    Pine::Renderer2D::RendererData m_RendererData2D{};
    Pine::OrthographicCameraController m_CameraController;

    std::shared_ptr<Pine::Framebuffer> m_Framebuffer;
    std::shared_ptr<Pine::Texture2D> m_ImageTexture;

    ZED::RecordManager m_RecordManager{};
    ZED::CameraParameters m_CameraParameters{};
    ZED::CameraSettings m_CameraSettings{};
    ZED::ImageConfiguration m_ImageConfig{};

    StaticSeries<float, 400> m_Pressure;
    StaticSeries<float, 400> m_TemperatureLeft;
    StaticSeries<float, 400> m_TemperatureRight;

    StaticSeries<float, 400> m_AccX;
    StaticSeries<float, 400> m_AccY;
    StaticSeries<float, 400> m_AccZ;

    StaticSeries<float, 400> m_AngX;
    StaticSeries<float, 400> m_AngY;
    StaticSeries<float, 400> m_AngZ;

    bool m_ViewportFocused = false;
    bool m_ViewportHovered = false;

    std::unordered_map<std::string, PanelLayout> m_PanelLayouts{};
};

} // namespace Pineapple
