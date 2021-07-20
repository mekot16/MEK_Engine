#pragma once

#include "MEK/Layer.h"

#include "MEK/Events/ApplicationEvent.h"
#include "MEK/Events/KeyEvent.h"
#include "MEK/Events/MouseEvent.h"

namespace MEK {

	class MEK_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		// This is so layers can do their own ImGui rendering
		void Begin();
		void End();

	private:
		float m_Time = 0.0f;

	};

}

