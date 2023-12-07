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
#include "Mesh.h"

void InitScene01(Scene& scene, const Canvas& canvas);
void InitScene02(Scene& scene, const Canvas& canvas);
void InitScene03(Scene& scene, const Canvas& canvas);
void InitScene04(Scene& scene, const Canvas& canvas);


int main(int argc, char**) {
	const int width = 800;
	const int height = 600;
	const int samples = 20;
	const int depth = 3;

	seedRandom((unsigned int)time(nullptr));


	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", width, height);



	Canvas canvas(width, height, renderer);
	Scene scene(glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f });

	InitScene01(scene, canvas);
	InitScene03(scene, canvas);

	// render scene
	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas, samples, depth);
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

void InitScene01(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	// create objects -> add to scene
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

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));
}


void InitScene02(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	//auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	//scene.AddObject(std::move(triangle));

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));

	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
	mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));
}


void InitScene03(Scene& scene, const Canvas& canvas)
{
	//float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	//std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 25 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	//scene.SetCamera(camera);

	
	

	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(glm::vec3{ 1.0f, 1.0f, 1.0f }));
	mesh->Load("models/man.fbx", glm::vec3{ 0.0f, 0.0f, -10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 1 });
	scene.AddObject(std::move(mesh));

	mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(glm::vec3{ 1.0f, 1.0f, 0.0f }));
	mesh->Load("models/cube.obj", glm::vec3{ -1.7f, 0.5f, -11.5f }, glm::vec3{ 0, 12, 0 }, glm::vec3{ 2, 4, 2 });
	scene.AddObject(std::move(mesh));

	auto quad = std::make_unique<Plane>(glm::vec3{ 0, 5, -10 }, glm::vec3{ 0, -1, 0 }, std::make_shared<Emissive>(glm::vec3{ 1.0f, 1.0f, 1.0f }));
	scene.AddObject(std::move(quad));

	quad = std::make_unique<Plane>(glm::vec3{ 0, -5, -10 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(glm::vec3{ 1.0f, 1.0f, 1.0f }));
	scene.AddObject(std::move(quad));

	quad = std::make_unique<Plane>(glm::vec3{ -5, 0, -10 }, glm::vec3{ 1, 0, 0 }, std::make_shared<Lambertian>(glm::vec3{ 1.0f, 0, 0 }));
	scene.AddObject(std::move(quad));

	quad = std::make_unique<Plane>(glm::vec3{ 5, 0, -10 }, glm::vec3{ -1, 0, 0 }, std::make_shared<Lambertian>(glm::vec3{ 0, 1.0f, 0 }));
	scene.AddObject(std::move(quad));

	quad = std::make_unique<Plane>(glm::vec3{ 0, 0, -15 }, glm::vec3{ 0, 0, 1 }, std::make_shared<Lambertian>(glm::vec3{ 1.0f, 1.0f, 1.0f }));
	scene.AddObject(std::move(quad));

	quad = std::make_unique<Plane>(glm::vec3{ 0, 0, 26 }, glm::vec3{ 0, 0, -1 }, std::make_shared<Lambertian>(glm::vec3{ 1, 1, 1 }));
	scene.AddObject(std::move(quad));

	
}
void InitScene04(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);



	auto quad = std::make_unique<Mesh>(std::make_shared<Lambertian>(glm::vec3{ 1 }));
	quad->Load("models/quad.obj", glm::vec3{ 0, 0, -13 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 20 });
	scene.AddObject(std::move(quad));
}