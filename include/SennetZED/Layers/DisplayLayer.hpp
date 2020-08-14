#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

#include <Sennet/Sennet.hpp>

#include <SennetZED/Messages/Request.hpp>
#include <SennetZED/Messages/Response.hpp>

namespace Sennet
{

namespace ZED
{

class DisplayLayer : public Layer
{
public:
	DisplayLayer();
	~DisplayLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Timestep ts) override;
	virtual void OnImGuiRender() override;

	virtual void OnEvent(Event& event) override;
	virtual void OnMessage(Ref<Message> msg) override;

private:
	bool OnImageMessage(Ref<ImageMessage> msg);
	bool OnStateResponse(Ref<StateResponse> msg);

private:
	Sennet::Ref<Sennet::VertexArray> m_SquareVa;
	Sennet::OrthographicCameraController m_CameraController;
};

}
}
