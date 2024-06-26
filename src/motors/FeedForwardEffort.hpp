#pragma once

#include <string>
#include <base/Eigen.hpp>
#include <base-logging/Logging.hpp>
#include <configmaps/ConfigMap.hpp>

// TODO: add constructor with configmap

namespace envire
{
    namespace types
    {
        namespace motors
        {
            struct FeedForwardEffort
            {
                FeedForwardEffort() {}
                FeedForwardEffort(configmaps::ConfigMap configMap_) : configMap(configMap_)
                {

                    maxEffortControl = false;
                    if (configMap.hasKey("name")
                        && configMap.hasKey("minValue") && configMap.hasKey("maxValue")
                        && configMap.hasKey("maxEffort") && configMap.hasKey("maxSpeed"))
                    {
                        name = configMap["name"].toString();
                        minValue = configMap["minValue"];
                        maxValue = configMap["maxValue"];
                        maxEffort = configMap["maxEffort"];
                        maxSpeed = configMap["maxSpeed"];

                        // we avoid the value dublication
                        // delete the keys, since we stored their values as class parameters
                        configMap.erase("name");
                        configMap.erase("minValue");
                        configMap.erase("maxValue");
                        configMap.erase("maxEffort");
                        configMap.erase("maxSpeed");
                    }
                    else
                    {
                        LOG_ERROR_S << "The config map has no all required keys";
                        configMap.clear();
                    }
                    if(configMap.hasKey("maxEffortControl"))
                    {
                        maxEffortControl = configMap["maxEffortControl"];
                        configMap.erase("maxEffortControl");
                    }
                }

                std::string name;
                static inline std::string const type = "ff_torque";
                configmaps::ConfigMap configMap;

                double minValue, maxValue;
                double maxEffort;
                double maxSpeed;
                bool maxEffortControl;

                configmaps::ConfigMap getFullConfigMap() {
                    configmaps::ConfigMap config;
                    config.append(configMap);
                    config["name"] = name;
                    config["type"] = type;
                    configMap["minValue"] = minValue;
                    configMap["maxValue"] = maxValue;
                    config["maxEffort"] = maxEffort;
                    config["maxSpeed"] = maxSpeed;
                    config["maxEffortControl"] = maxEffortControl;
                    return config;
                }

                /**Grants access to boost serialization */
                friend class boost::serialization::access;

                /**Serializes the members of this class*/
                template <typename Archive>
                void serialize(Archive &ar, const unsigned int version)
                {
                    throw std::runtime_error("envire::types::MotorFeedForwardEffort serialize not implemented");
                }
            };
        }
    }
}
