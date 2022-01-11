#pragma once
#include "Map.h"
/// <summary>
/// Base class for each component 
/// </summary>

class Component
{
public:
   virtual ~Component() = default;
   virtual void init(int x,int y,int lvl,Map*m) = 0;//coordonatele x,y
   //virtual void update() = 0;
   virtual void draw() = 0;
};