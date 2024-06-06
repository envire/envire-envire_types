#include "TypeCreatorRegistration.hpp"

// Note: all type registrations should be down in one cpp file
// to generate an unique TypeCreator for each type

#include "../World.hpp"
ENVIRE_TYPE_CREATOR_REGISTRATION( envire::types::World )

#include "../Link.hpp"
ENVIRE_TYPE_CREATOR_REGISTRATION( envire::types::Link )
#include "../Inertial.hpp"
ENVIRE_TYPE_CREATOR_REGISTRATION( envire::types::Inertial )

#include "../joints/Continuous.hpp"
ENVIRE_TYPE_CREATOR_REGISTRATION( envire::types::joints::Continuous )
#include "../joints/Fixed.hpp"
ENVIRE_TYPE_CREATOR_REGISTRATION( envire::types::joints::Fixed )
#include "../joints/Revolute.hpp"
ENVIRE_TYPE_CREATOR_REGISTRATION( envire::types::joints::Revolute )
#include "../joints/Prismatic.hpp"
ENVIRE_TYPE_CREATOR_REGISTRATION( envire::types::joints::Prismatic )

#include "../geometry/Box.hpp"
ENVIRE_TYPE_CREATOR_REGISTRATION( envire::types::geometry::Box )
#include "../geometry/Capsule.hpp"
ENVIRE_TYPE_CREATOR_REGISTRATION( envire::types::geometry::Capsule )
#include "../geometry/Cylinder.hpp"
ENVIRE_TYPE_CREATOR_REGISTRATION( envire::types::geometry::Cylinder )
#include "../geometry/Mesh.hpp"
ENVIRE_TYPE_CREATOR_REGISTRATION( envire::types::geometry::Mesh )
#include "../geometry/Plane.hpp"
ENVIRE_TYPE_CREATOR_REGISTRATION( envire::types::geometry::Plane )
#include "../geometry/Sphere.hpp"
ENVIRE_TYPE_CREATOR_REGISTRATION( envire::types::geometry::Sphere )

#include "../motors/DC.hpp"
ENVIRE_TYPE_CREATOR_REGISTRATION( envire::types::motors::DC )
#include "../motors/PID.hpp"
ENVIRE_TYPE_CREATOR_REGISTRATION( envire::types::motors::PID )
#include "../motors/DirectEffort.hpp"
ENVIRE_TYPE_CREATOR_REGISTRATION( envire::types::motors::DirectEffort )
#include "../motors/FeedForwardEffort.hpp"
ENVIRE_TYPE_CREATOR_REGISTRATION( envire::types::motors::FeedForwardEffort )

#include "../sensors/CameraSensor.hpp"
ENVIRE_TYPE_CREATOR_REGISTRATION( envire::types::sensors::CameraSensor )
#include "../sensors/RaySensor.hpp"
ENVIRE_TYPE_CREATOR_REGISTRATION( envire::types::sensors::RaySensor )
