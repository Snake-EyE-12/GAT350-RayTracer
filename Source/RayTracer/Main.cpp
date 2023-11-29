#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"

int main(int argc, char**) { 
	seedRandom((unsigned int)time(nullptr));





	std::cout << "Hello World!" << std::endl;

	Renderer renderer;
	renderer.Initialize();

	renderer.CreateWindow("RayTracing", 400, 300);
	Canvas canvas(400, 300, renderer);

	bool quit = false;

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	Scene scene; // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	while (!quit) {

		canvas.Clear({ 0, 0, 0, 1 });
		scene.Render(canvas);
		canvas.Update();

		renderer.PresentCanvas(canvas);


		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			}
			break;
		}
		}
	}


	renderer.Shutdown();


	return 0;
}