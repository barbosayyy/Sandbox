#pragma once

#include "Core/Types.h"
#include "Engine/IEngine.h"
#include "ImGui/ImGuiSbContext.h"
#include "Rendering/Renderer.h"
#include "ECS/Registry.h"
#include "Resources/ResourceManager.h"

#include <memory>

namespace Sb {
	class Engine final : public IEngine {
	public:
		Engine();
		~Engine();

		// Engine components Get/Set
			void SetRenderer(Renderer& renderer);
			void SetInputManager(InputManager& inputManager);
			void SetECSRegistry(ECS::Registry& registry);
			void SetResourceManager(ResourceManagement::ResourceManager& resourceManager);
			Renderer& GetRenderer() const final override { return *_renderer; };
			InputManager& GetInputManager() const final override { return *_internalInput; };
			ECS::Registry& GetECSRegistry() const final override { return *_ecsRegistry; };
			ResourceManagement::ResourceManager& GetResourceManager() const final override { return *_resourceManager; };
		
		// Engine functionality
		void SetUIRenderingEnabled(bool enable) final override { _uiRenderEnabled = enable; };
		Stats GetStats() const final override { return _gameStats; };
		Config GetConfig() const final override { return _engineConfig; };

		// Verifies engine subsystems' status
		bool Validate();

		// Runs initial setup
		void Start();

		// Update backend state
		void Update();

		// Render
		void Render();

		// Late render
		void LateRender();

		// Call after game stop and before application exit
		void Stop();

		void OnInput();

		private:
		Renderer* _renderer;
		InputManager* _internalInput;
		ECS::Registry* _ecsRegistry;
		ResourceManagement::ResourceManager* _resourceManager;
		
		bool _uiRenderEnabled;

		// Runtime stats + config
		Stats _engineStats;
		Stats _gameStats;
		Config _engineConfig;

		static bool _error;
		bool _firstFrame;
	};
}
