#ifndef MATERIALRES_H
#define MATERIALRES_H

#include "resource.h"
#include "material.h"

class MaterialRes : public Resource
{
public:
	MaterialRes(const char *arg_name, Material *arg_mat);
	~MaterialRes();

private:
	Material *mMaterial;

public:
	void Reload() override;

	Material *GetMaterial();


};


#endif