#pragma once

#include <string>
#include <configmaps/ConfigMap.hpp>
#include <base-logging/Logging.hpp>
#include <boost/serialization/access.hpp>

namespace envire
{
    namespace types
    {
        namespace sensors {
            struct RotatingRaySensor
            {
                RotatingRaySensor() {}

                RotatingRaySensor(configmaps::ConfigMap configMap_) : configMap(configMap_)
                {
                    if (configMap.hasKey("name"))
                    {
                        name = configMap["name"].toString();

                        // we avoid the value dublication
                        // delete the keys, since we stored their values as class parameters
                        configMap.erase("name");
                    }
                    else
                    {
                        LOG_ERROR_S << "The config map has no all required keys";
                        configMap.clear();
                    }
                }

                std::string name;
                configmaps::ConfigMap configMap;

                configmaps::ConfigMap getFullConfigMap() {
                    configmaps::ConfigMap config;
                    config.append(configMap);
                    config["name"] = name;
                    return config;
                }

                /**Grants access to boost serialization */
                friend class boost::serialization::access;

                /**Serializes the members of this class*/
                template <typename Archive>
                void serialize(Archive &ar, const unsigned int version)
                {
                    throw std::runtime_error("envire::types::RotatingRaySensor serialize not implemented");
                }
            };
        }
    }
}
