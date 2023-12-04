#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include <vector>

int main(int argc, char**) { 
	seedRandom((unsigned int)time(nullptr));

	std::cout << "Hello World!" << std::endl;

	Renderer renderer;
	renderer.Initialize();

	renderer.CreateWindow("RayTracing", 800, 600);
	Canvas canvas(800, 600, renderer);


	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	Scene scene(10); // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	
	// create material
	auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
	auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);

	// create objects -> add to scene
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<Material> material = ((int)random(0, 2) == 0) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
		auto sphere = std::make_unique<Sphere>(random({ -2, -2, -1 }, { 2, 2, -7 }), random(0.2, 0.4), material);
		scene.AddObject(std::move(sphere));
	
	
	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas, 30);
	canvas.Update();

	bool quit = false;
	while (!quit)
	{

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
		renderer.PresentCanvas(canvas);
	}


	renderer.Shutdown();


	return 0;
}