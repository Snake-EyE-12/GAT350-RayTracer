#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include <vector>
#include "Plane.h"
#include "Triangle.h"
#include <glm/gtx/color_space.hpp>

int main(int argc, char**) {
	seedRandom((unsigned int)time(nullptr));

	std::cout << "Hello World!" << std::endl;

	Renderer renderer;
	renderer.Initialize();

	renderer.CreateWindow("RayTracing", 800, 600);
	Canvas canvas(800, 600, renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 1, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);


	Scene scene(8, glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f });
	scene.SetCamera(camera);


	for (int x = -10; x < 10; x++)
	{
		for (int z = -10; z < 10; z++)
		{

			std::shared_ptr<Material> material;

			// create random material
			float r = random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}

	std::shared_ptr<Material> material = std::make_shared<Lambertian>(color3_t{ 0.2 });
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0,  0 }, glm::vec3{ 0, 1, 0 }, material);
	scene.AddObject(std::move(plane));
	/*
	std::shared_ptr<Material> triangleMaterial = std::make_shared<Lambertian>(color3_t{ 0.9f, 0.5f, 0.5f });
	auto tri = std::make_unique<Triangle>(glm::vec3{ 0, 1,  -3 }, glm::vec3{ 2, 1, -3 }, glm::vec3{ 1.5f, 2.5f, -3 }, triangleMaterial);
	scene.AddObject(std::move(tri));
	{ // Planes
		std::shared_ptr<Material> material = std::make_shared<Lambertian>(color3_t{ 0.5f, 1.0f, 0.5f });
		auto planeGreen = std::make_unique<Plane>(glm::vec3{ 20, 0, 0 }, glm::vec3{ -1, 0, 0 }, material);
		scene.AddObject(std::move(planeGreen));

		material = std::make_shared<Lambertian>(color3_t{ 0.9f, 0.4f, 0.4f });
		auto planeRed = std::make_unique<Plane>(glm::vec3{ -20, 0, 0 }, glm::vec3{ 1, 0, 0 }, material);
		scene.AddObject(std::move(planeRed));

		// White Walls
		material = std::make_shared<Lambertian>(color3_t{ 0.95f, 0.95f, 0.85f });
		auto planeWhite = std::make_unique<Plane>(glm::vec3{ 0, -20, 0 }, glm::vec3{ 0, 1, 0 }, material);
		scene.AddObject(std::move(planeWhite));

		planeWhite = std::make_unique<Plane>(glm::vec3{ 0, 0, -40 }, glm::vec3{ 0, 0, 1 }, material);
		scene.AddObject(std::move(planeWhite));
	}*/

	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas, 10);
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