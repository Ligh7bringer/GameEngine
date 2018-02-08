#include "scene.h"
#include "system_renderer.h"

void Scene::Update(double dt)
{
}

void Scene::Render()
{
}

std::vector<std::shared_ptr<Entity>>& Scene::getEnts()
{
	return _ents.list;
}
