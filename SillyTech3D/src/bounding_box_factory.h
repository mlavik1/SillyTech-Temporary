#ifndef BOUNDINGBOXFACTORY_H
#define BOUNDINGBOXFACTORY_H

#include "resource_manager.h"
#include "bounding_box.h"
#include "actor.h"
#include "mesh_data.h"

//class MeshData;

class BoundingBoxFactory
{
public:
	
	/*Creates a bounding box, and returns the resource ID
	* Note: Will not buffer the mesh data
	*/
	static BoundingBox *CreateBoundingBox(Actor *arg_actor);
	static BoundingBox *CreateBoundingBox(MeshData *arg_meshdata);
	
};

#endif