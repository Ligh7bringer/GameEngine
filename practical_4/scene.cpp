#include "scene.h"
#include "system_renderer.h"

void Scene::Update(double dt)
{
}

void Scene::Render()
{
	for (auto &_e : _ents.list) {
		_e->Render();
	}
}

std::vector<std::shared_ptr<Entity>>& Scene::getEnts()
{
	return _ents.list;
}
