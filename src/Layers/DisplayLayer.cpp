#include <SennetZED/Layers/DisplayLayer.hpp>

namespace Sennet
{

namespace ZED
{

DisplayLayer::DisplayLayer()
	: m_CameraController(1280.0f / 720.0f, false)
{
	m_SquareVa = Sennet::VertexArray::Create();

	float squareVertices[4 * 5] = 
	{
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};
	
	Sennet::Ref<Sennet::VertexBuffer> squareVb(
		Sennet::VertexBuffer::Create(squareVertices,
		sizeof(squareVertices)));

	squareVb->SetLayout({
		{ Sennet::ShaderDataType::Float3, "a_Position" },
		{ Sennet::ShaderDataType::Float2, "a_TexCoord" }
	});

	m_SquareVa->AddVertexBuffer(squareVb);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

	Sennet::Ref<Sennet::IndexBuffer> squareIb(
		Sennet::IndexBuffer::Create(squareIndices,
		sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVa->SetIndexBuffer(squareIb);
}

DisplayLayer::~DisplayLayer()
{
}

void DisplayLayer::OnAttach()
{
}

void DisplayLayer::OnDetach()
{
}

void DisplayLayer::OnUpdate(Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
	RenderCommand::Clear();
}

void DisplayLayer::OnImGuiRender()
{
}

void DisplayLayer::OnEvent(Event& event)
{
	m_CameraController.OnEvent(event);
}

void DisplayLayer::OnMessage(Ref<Message> msg)
{
	MessageDispatcher dispatcher(msg);
	dispatcher.Dispatch<Sennet::ImageMessage>(
		std::bind(&DisplayLayer::OnImageMessage, this,
		std::placeholders::_1));
	dispatcher.Dispatch<StateResponse>(
		std::bind(&DisplayLayer::OnStateResponse, this,
		std::placeholders::_1));
}

bool DisplayLayer::OnImageMessage(Ref<Sennet::ImageMessage> msg)
{
	return false;
}

bool DisplayLayer::OnStateResponse(Ref<StateResponse> msg)
{
	return false;
}

}
}
