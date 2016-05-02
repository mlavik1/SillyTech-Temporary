#ifndef ACTORFACTORY_H
#define ACTORFACTORY_H

#include <scene.h>
#include <postprocess.h>
#include <Importer.hpp>
#include "actor.h"
#include "mesh_render_component.h"


class ActorFactory
{
public:
	static Actor* CreateFromModel(const char* arg_path);

};

#endif