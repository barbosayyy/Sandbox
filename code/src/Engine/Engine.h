#pragma once

#include "Engine/IEngine.h"
#include "ImGui/ImGuiSbContext.h"
#include "Rendering/Renderer.h"
#include "Scene/SceneManager.h"

#include <memory>
namespace Sb {
	class Engine : public IEngine {
	public:
		Engine();
		~Engine();
		void SetRenderer(Renderer& renderer);
		void SetInputManager(InputManager& inputManager);

		Renderer& GetRenderer() const { return *_renderer; };
		InputManager& GetInputManager() const { return *_internalInput; };

		// Returns internal struct containing engine stats
		Stats GetStats() const { return _gameStats; };

		Config GetConfig() const { return _engineConfig; };

		// Verifies engine subsystems' status
		bool Validate();

		// Runs initial setup
		void Start();

		// Update backend state
		void Update();

		// Prepare the renderer's new frame
		void BeginNewFrame();

		// Render Engine-side elements
		void Render();

		// Call after game stop and before application exit
		void Stop();

		void OnInput();

	private:
		Renderer* _renderer;
		InputManager* _internalInput;
		// SceneManager* _sceneManager;

		// Exposed sgame stats
		Stats _gameStats;

		// Internal stats
		Stats _engineStats;

		Config _engineConfig;

		static bool _error;
	};
}
