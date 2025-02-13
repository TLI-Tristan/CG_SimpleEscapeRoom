#ifndef MATERIAL_H
#define MATERIAL_H

struct Component
{
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f)
	{
		Set(r, g, b);
	}
	void Set(float r, float g, float b)
	{
		this->r = r; this->g = g; this->b = b;
	}
};

struct Material
{
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;
	
	Material()
	{
		kAmbient.Set(0.05f, 0.05f, 0.05f);
		kDiffuse.Set(0.6f, 0.6f, 0.6f);
		kSpecular.Set(0.2f, 0.2f, 0.2f);
		kShininess = 5.f;
	}
};


#endif