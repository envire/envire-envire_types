#pragma once

#include <string>
#include <configmaps/ConfigMap.hpp>
#include <base-logging/Logging.hpp>
#include <boost/serialization/access.hpp>

// TODO: add constructor with configmap

namespace envire
{
    namespace types
    {
        namespace sensors {
            struct RaySensor
            {
                RaySensor() {}

                RaySensor(configmaps::ConfigMap configMap_) : configMap(configMap_)
                {
                    if (configMap.hasKey("name")
                        && configMap.hasKey("maxDistance")
                        && configMap.hasKey("opening_width"))
                    {
                        name = configMap["name"].toString();
                        maxDistance = configMap["maxDistance"];
                        openingWidth = configMap["opening_width"];

                        // we avoid the value dublication
                        // delete the keys, since we stored their values as class parameters
                        configMap.erase("name");
                        configMap.erase("maxDistance");
                        configMap.erase("opening_width");
                    }
                    else
                    {
                        LOG_ERROR_S << "The config map has no all required keys";
                        configMap.clear();
                    }
                }

                std::string name;
                configmaps::ConfigMap configMap;

                double maxDistance;
                double openingWidth;

                configmaps::ConfigMap getFullConfigMap() {
                    configmaps::ConfigMap config;
                    config.append(configMap);
                    config["name"] = name;
                    config["maxDistance"] = maxDistance;
                    config["openingWidth"] = openingWidth;
                    return config;
                }

                /**Grants access to boost serialization */
                friend class boost::serialization::access;

                /**Serializes the members of this class*/
                template <typename Archive>
                void serialize(Archive &ar, const unsigned int version)
                {
                    throw std::runtime_error("envire::types::MotorDC serialize not implemented");
                }
            };
        }
    }
}
