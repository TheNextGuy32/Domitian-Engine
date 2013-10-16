#define DomitianEngine

/*
- do nothing if: A makes no references at all to B
- do nothing if: The only reference to B is in a friend declaration
- forward declare B if: A contains a B pointer or reference: B* myb;
- forward declare B if: one or more functions has a B object/pointer/reference
as a parementer, or as a return type: B MyFunction(B myb);
- #include "b.h" if: B is a parent class of A
- #include "b.h" if: A contains a B object: B myb;
*/

//Game Objects
#include "Entity.h"

//Graphics
#include "SpriteComp.h"
#include "AnimatedComp.h"

//Infastructure
#include "PositionComp.h"

#include "PhysicsComp.h"
#include "Force.h"

//Utility
#include "Vector2.h"
#include "Vector3.h"
#include "Radian.h"

