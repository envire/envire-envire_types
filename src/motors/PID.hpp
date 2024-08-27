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
            struct PID
            {
                PID() {}
                PID(configmaps::ConfigMap configMap_) : configMap(configMap_)
                {
                    if (configMap.hasKey("name")
                        && configMap.hasKey("p") && configMap.hasKey("i") && configMap.hasKey("d")
                        && configMap.hasKey("minValue") && configMap.hasKey("maxValue")
                        && configMap.hasKey("maxEffort") && configMap.hasKey("maxSpeed"))
                    {
                        name = configMap["name"].toString();
                        p = configMap["p"];
                        i = configMap["i"];
                        d = configMap["d"];
                        minPosition = configMap["minValue"];
                        maxPosition = configMap["maxValue"];
                        maxEffort = configMap["maxEffort"];
                        maxSpeed = configMap["maxSpeed"];

                        // we avoid the value dublication
                        // delete the keys, since we stored their values as class parameters
                        configMap.erase("name");
                        configMap.erase("p");
                        configMap.erase("i");
                        configMap.erase("d");
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
                }

                std::string name;
                const std::string& getName() const
                {
                    return name;
                }
                static inline std::string const type = "PID";
                configmaps::ConfigMap configMap;

                double p;
                double i;
                double d;
                double minPosition;
                double maxPosition;
                double maxEffort;
                double maxSpeed;

                configmaps::ConfigMap getFullConfigMap() {
                    configmaps::ConfigMap config;
                    config.append(configMap);
                    config["name"] = name;
                    config["type"] = type;
                    config["p"] = p;
                    config["i"] = i;
                    config["d"] = d;
                    config["minPosition"] = minPosition;
                    config["maxPosition"] = maxPosition;
                    config["maxEffort"] = maxEffort;
                    config["maxSpeed"] = maxSpeed;
                    return config;
                }

                /**Grants access to boost serialization */
                friend class boost::serialization::access;

                /**Serializes the members of this class*/
                template <typename Archive>
                void serialize(Archive &ar, const unsigned int version)
                {
                    throw std::runtime_error("envire::types::MotorPID serialize not implemented");
                }
            };
        }
    }
}
