find_package(PluginManager)

# for debugging to test get precomplited units
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -E")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -E")

find_package(Boost COMPONENTS serialization filesystem system thread)

rock_library(envire_types
    SOURCES
        registration/TypeCreatorFactory.cpp
        registration/TypeRegistration.cpp
    HEADERS
        EnvireTypeBase.hpp
        World.hpp
        Link.hpp
        Inertial.hpp
        geometry/Heightfield.hpp
        geometry/Box.hpp
        geometry/Capsule.hpp
        geometry/Cylinder.hpp
        geometry/Mesh.hpp
        geometry/Plane.hpp
        geometry/Sphere.hpp
        geometry/Material.hpp
        joints/Fixed.hpp
        joints/Continuous.hpp
        joints/Revolute.hpp
        joints/Prismatic.hpp
        motors/DC.hpp
        motors/PID.hpp
        motors/DirectEffort.hpp
        motors/FeedForwardEffort.hpp
        sensors/CameraSensor.hpp
        sensors/RaySensor.hpp
        sensors/RotatingRaySensor.hpp
        sensors/Joint6DOFSensor.hpp
        registration/TypeCreatorInterface.hpp
        registration/TypeCreatorFactory.hpp
        registration/TypeCreatorRegistration.hpp
    DEPS_PKGCONFIG
        base-types
        configmaps
        base-logging
        envire_core
    DEPS_PLAIN
        Boost_FILESYSTEM
        Boost_SERIALIZATION
        Boost_SYSTEM
        Boost_THREAD
)

install_plugin_info(envire_types)
add_compile_definitions(SCHEMA_PATH=\"${CMAKE_INSTALL_PREFIX}/share/envire_types/schema\")
