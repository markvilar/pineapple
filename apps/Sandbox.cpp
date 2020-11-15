#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Image.hpp"
#include "Sennet/ZED/SensorController.hpp"

#include <imgui.h>

class TestLayer : public Sennet::Layer
{
public:
	TestLayer()
		: Layer("Test"), m_CameraController(1200.0f / 720.0f)
	{
	}

	~TestLayer()
	{
	}
	
	void OnAttach() override
	{
		m_Texture = Sennet::Texture2D::Create(2560, 720,
			Sennet::Texture::InternalFormat::RGBA8,
			Sennet::Texture::DataFormat::BGRA);
		m_SensorController.Initialize();
	}

	void OnDetach() override
	{
		m_SensorController.Shutdown();
	}

	void OnUpdate(Sennet::Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);
		Sennet::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f});
		Sennet::RenderCommand::Clear();

		Sennet::Renderer2D::BeginScene(m_CameraController.GetCamera());

		if (m_SensorController.IsRecording())
		{
			auto image = m_SensorController.GetImage(
				Sennet::ZED::View::SideBySide);
			SN_INFO("Image size: {0} ({1}, {2}, {3})", 
				image->GetSize(), image->GetWidth(),
				image->GetHeight(), image->GetChannels());
			if (image->GetSize() > 0)
			{
				m_Texture->SetData(image->GetPtr(), 
					image->GetSize());
				Sennet::Renderer2D::DrawQuad({ 0.0f, 0.0f }, 
					{ 3.2f, -0.9f }, m_Texture);
			}
		}
		else
		{
			Sennet::Renderer2D::DrawQuad({ 0.0f, 0.0f }, 
				{ 3.2f, -0.9f }, { 0.8f, 0.2f, 0.2f, 1.0f });
		}
		
		Sennet::Renderer2D::EndScene();
	}

	void OnImGuiRender() override
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
		
		ImGui::Begin("Recorder");
		if (ImGui::Button("Start Record"))
		{
			if (!m_SensorController.IsRecording())
				m_SensorController.Start();
		}

		if (ImGui::Button("Stop Record"))
		{
			if (m_SensorController.IsRecording())
				m_SensorController.Stop();
		}
		ImGui::End();
	}

	void OnEvent(Sennet::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}
	
private:
	Sennet::OrthographicCameraController m_CameraController;
	Sennet::Ref<Sennet::Texture2D> m_Texture;

	Sennet::ZED::SensorController m_SensorController;
};

class TestApplication : public Sennet::Application
{
public:
	TestApplication() : Application()
	{
		PushLayer(new TestLayer());
	}

	~TestApplication()
	{
	}
};

Sennet::Application* Sennet::CreateApplication()
{
	return new TestApplication();
}

int Sennet::main(int argc, char** argv)
{
	Sennet::Log::Init();
	auto app = Sennet::CreateApplication();
	app->Run();
	return 0;
}

int main(int argc, char** argv)
{	
	return Sennet::main(argc, argv);
}
