#pragma once

#include <string>
#include <base/Eigen.hpp>
#include <base-logging/Logging.hpp>
#include <boost/serialization/access.hpp>
#include <configmaps/ConfigMap.hpp>

// TODO: motors has maxSpeed and joint maxVelocity, find one config name
// TODO: add shemas
namespace envire
{
    namespace types
    {
        namespace joints
        {
            struct Continuous
            {
                Continuous() {}

                Continuous(configmaps::ConfigMap configMap_) : configMap(configMap_)
                {
                    if (configMap.hasKey("name") && configMap.hasKey("axis")
                        && configMap["axis"].hasKey("x") && configMap["axis"].hasKey("y") && configMap["axis"].hasKey("z")
                        && configMap.hasKey("maxEffort") && configMap.hasKey("maxVelocity"))
                    {
                        name = configMap["name"].toString();
                        axis = base::Vector3d(configMap["axis"]["x"], configMap["axis"]["y"], configMap["axis"]["z"]);
                        maxEffort = configMap["maxEffort"];
                        maxVelocity = configMap["maxVelocity"];

                        // we avoid the value dublication
                        // delete the keys, since we stored their values as class parameters
                        configMap.erase("name");
                        configMap.erase("axis");
                        configMap.erase("maxEffort");
                        configMap.erase("maxVelocity");
                    }
                    else
                    {
                        LOG_ERROR_S << "The config map has no all required keys";
                        axis = base::Vector3d::Zero();
                        configMap.clear();
                    }
                }

                std::string name;
                const std::string& getName() const
                {
                    return name;
                }
                static inline std::string const type = "continuous";
                configmaps::ConfigMap configMap;

                base::Vector3d axis;
                double maxEffort;
                double maxVelocity;

                configmaps::ConfigMap getFullConfigMap() {
                    configmaps::ConfigMap config;
                    config.append(configMap);
                    config["name"] = name;
                    config["type"] = type;
                    config["axis"]["x"] = axis.x();
                    config["axis"]["y"] = axis.y();
                    config["axis"]["z"] = axis.z();
                    config["maxEffort"] = maxEffort;
                    config["maxVelocity"] = maxVelocity;
                    return config;
                }

                /**Grants access to boost serialization */
                friend class boost::serialization::access;

                /**Serializes the members of this class*/
                template <typename Archive>
                void serialize(Archive &ar, const unsigned int version)
                {
                    throw std::runtime_error("envire::types::Box serialize not implemented");
                }
            };
        }
    }
}
