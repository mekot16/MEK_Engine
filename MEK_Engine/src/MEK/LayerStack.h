#pragma once

#include "MEK/Core.h"
#include "Layer.h"

#include <vector>

namespace MEK {

	class MEK_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		// this class is essentially a wrapper over this vector of Layers
		// layers get pushed into first half of vector, overlays into second half
		std::vector<Layer*> m_Layers;
		// keeps track of the last layer, before overlays
		// ex: <layer layer layer | overlay>, where | is m_LayerInsesrt
		unsigned int m_LayerInsertIndex = 0;
	};

}


