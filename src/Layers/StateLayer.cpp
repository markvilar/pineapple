#include <SennetZED/Layers/StateLayer.hpp>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

// Temporary.
#include <Sennet/Platform/OpenGL/OpenGLShader.hpp>

namespace Sennet
{

namespace ZED
{

static unsigned short StringToUnsignedShort(const std::string s)
{
	auto number = std::strtoul(s.c_str(), NULL, 0);
	if (number > USHRT_MAX)
	{
		return 0;
	}

	return (unsigned short) number;
}

StateLayer::StateLayer()
	: Layer("State"), m_CameraController(1280.0f / 720.0f, false)
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

	std::string textureShaderVertexSrc = R"(
		#version 330 core
		
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec2 a_TexCoord;
		uniform mat4 u_ViewProjection;
		uniform mat4 u_Transform;
		out vec2 v_TexCoord;
		void main()
		{
			v_TexCoord = a_TexCoord;
			gl_Position = u_ViewProjection * u_Transform
				* vec4(a_Position, 1.0);	
		}
	)";

	std::string textureShaderFragmentSrc = R"(
		#version 330 core
		
		layout(location = 0) out vec4 color;
		in vec2 v_TexCoord;
		uniform sampler2D u_Texture;
		void main()
		{
			color = texture(u_Texture, v_TexCoord);
		}
	)";	

	m_TextureShader = Sennet::Shader::Create("Texture",
		textureShaderVertexSrc,
		textureShaderFragmentSrc);

	std::dynamic_pointer_cast<Sennet::OpenGLShader>(
		m_TextureShader)->Bind();	

	m_Texture = Sennet::Texture2D::Create(
		"/home/martin/dev/sennet-zed/assets/textures/checkerboard.png");

	std::dynamic_pointer_cast<Sennet::OpenGLShader>(
		m_TextureShader)->Bind();

	std::dynamic_pointer_cast<Sennet::OpenGLShader>(
		m_TextureShader)->UploadUniformInt("u_Texture", 0);
}

StateLayer::~StateLayer()
{
}

void StateLayer::OnAttach()
{
}

void StateLayer::OnDetach()
{
}

void StateLayer::OnUpdate(Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
	RenderCommand::Clear();

	Sennet::Renderer::BeginScene(m_CameraController.GetCamera());	

	// Create texture

	// Bind texture
	m_Texture->Bind();

	// Bind shader
	Sennet::Renderer::Submit(m_TextureShader, m_SquareVa, 
		glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		
	Sennet::Renderer::EndScene();
	
	if (m_ShouldMonitor)
	{
		SetupStateRequest();
	}
}

void StateLayer::OnImGuiRender()
{
	RenderStateWindow();
}

void StateLayer::OnEvent(Event& event)
{
	m_CameraController.OnEvent(event);
}

void StateLayer::OnMessage(Ref<Message> msg)
{
	MessageDispatcher dispatcher(msg);
	dispatcher.Dispatch<StateResponse>(
		std::bind(&StateLayer::OnStateResponse, this,
		std::placeholders::_1));
}

bool StateLayer::OnStateResponse(Ref<StateResponse> msg)
{
	m_Image = msg->GetImage();
	return false;
}

void StateLayer::SetupStateRequest()
{
	float time = glfwGetTime();
	auto timeSinceLastStateRequest = time - m_LastStateRequestTime;
	if (timeSinceLastStateRequest < 1.0f / m_StateRequestFrequency)
	{
		return;
	}

	auto connectionManager = ConnectionManager::GetPtr();
	if (!connectionManager)
	{
		return;
	}

	auto remoteEndpoints = connectionManager->GetRemoteEndpointsData();
	for (auto endpoint : *remoteEndpoints)
	{
		SubmitStateRequest(endpoint.first, endpoint.second);
	}
	m_LastStateRequestTime = glfwGetTime();
}

void StateLayer::SubmitStateRequest(const std::string address,
	const unsigned short port)
{
	auto connectionManager = Sennet::ConnectionManager::GetPtr();
	if (!connectionManager)
	{
		SN_WARN("Connection manager not initialized!");
		return;
	}

	auto connection = connectionManager->FindConnection(address, port);
	if (!connection)
	{
		SN_WARN("Could not find connection with remote endpoint: "
			"{0}:{1}", address, port);
		return;
	}

	auto msg = Sennet::CreateRef<StateRequest>(
		connection->GetLocalInformation().first,
		connection->GetLocalInformation().second);
	connectionManager->SubmitMessage(connection, msg);
}

void StateLayer::RenderStateWindow()
{
	ImGui::Begin("State Monitoring");

	RenderNodeSelectionHeader();
	RenderNodeStateHeader();
	
	ImGui::End();
}

void StateLayer::RenderNodeSelectionHeader()
{
	bool collapsed = !ImGui::CollapsingHeader("Node Selection");
	ImGui::SameLine();
	Sennet::ImGuiHelpMarker("Monitor the state of an active Sennet node.");

	if (collapsed)
		return;

	ImGui::Text("Monitoring Address: %s", m_MonitoringNodeAddress.c_str());
	ImGui::Text("Monitoring Port: 	 %s", m_MonitoringNodePort.c_str());

	ImGui::Separator();

	static char addressBuffer[20];
	static char portBuffer[10];
	ImGui::InputText("Address", addressBuffer, IM_ARRAYSIZE(addressBuffer));
	ImGui::InputText("Port", portBuffer, IM_ARRAYSIZE(portBuffer));
	
	if (ImGui::Button("Update Monitoring Node"))
	{
		StartMonitoringNode(addressBuffer, portBuffer);
	}

	ImGui::SameLine();

	if (ImGui::Button("Stop Monitoring"))
	{
		StopMonitoringNode();
	}

	ImGui::TreePop();
}

void StateLayer::RenderNodeStateHeader()
{
	bool collapsed = !ImGui::CollapsingHeader("Node State");
	ImGui::SameLine();
	Sennet::ImGuiHelpMarker("Display the state of an active Sennet node.");

	if (collapsed)
		return;

}

void StateLayer::StartMonitoringNode(const std::string address,
		const std::string port)
{
	auto connectionManager = Sennet::ConnectionManager::GetPtr();
	if (!connectionManager)
		return;

	auto connection = connectionManager->FindConnection(address,
		StringToUnsignedShort(port));
	if (!connection)
		return;

	m_MonitoringNodeAddress = address;
	m_MonitoringNodePort = port;
	m_ShouldMonitor = true;
}

void StateLayer::StopMonitoringNode()
{
	m_MonitoringNodeAddress = "";
	m_MonitoringNodePort = "";
	m_ShouldMonitor = false;
}

}
}
