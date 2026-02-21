#pragma once

#include "Core/Types.h"
#include "Client/IClient.h"
#include "Engine/IEngine.h"
#include "ImGui/ImGuiSbContext.h"
#include "Rendering/Renderer.h"
#include "ECS/Registry.h"
#include "Resources/ResourceManager.h"
#include "Scripting/ScriptRegistry.h"
#include "Game/GameService.h"

#include <memory>

namespace Sb {
	class Engine : public IEngine {
	public:
		Engine();
		~Engine();

		void InitContext(const String& name, IClient& client) override;
		void Context();
		void EndContext();

		bool ValidateContext();

		// Update backend state
		void Update();

		// Render
		void Render();

		// Late render
		void LateRender();

		// Call after game stop and before application exit
		void Stop();

		void OnInput();

		void SetRenderer(Renderer& instance);
		void SetInputManager(InputManager& instance);
		void SetECSRegistry(ECS::Registry& instance);
		void SetResourceManager(ResourceManagement::ResourceManager& instance);
		void SetScriptRegistry(Scripting::ScriptRegistry& instance);
		void SetUIRendering(bool enable) final override { _uiRender = enable; };

		Renderer& GetRenderer() const final override { return *_renderer; };
		InputManager& GetInputManager() const final override { return *_internalInput; };
		ECS::Registry& GetECSRegistry() const final override { return *_ecsRegistry; };
		ResourceManagement::ResourceManager& GetResourceManager() const final override { return *_resourceManager; };
		Stats GetStats() const final override { return _gameStats; };
		Config GetConfig() const final override { return _engineConfig; };

	private:
		Renderer* _renderer;
		InputManager* _internalInput;
		ECS::Registry* _ecsRegistry;
		ResourceManagement::ResourceManager* _resourceManager;
		Scripting::ScriptRegistry* _scriptRegistry;
		
		IClient* _client;
		GameService _gameService;
		
		// Runtime stats + config
		Stats _engineStats;
		Stats _gameStats;
		Config _engineConfig;
		
		bool _uiRender;
		static bool _error;
		bool _firstFrame;
	};
}
