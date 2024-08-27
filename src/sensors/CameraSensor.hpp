#pragma once

#include "../EnvireTypeBase.hpp"

#include <string>
#include <configmaps/ConfigMap.hpp>
#include <base-logging/Logging.hpp>
#include <boost/serialization/access.hpp>


namespace envire
{
    namespace types
    {
        namespace sensors
        {
            class CameraSensor: public EnvireTypeBase
            {
            public:
                CameraSensor() {}

                CameraSensor(configmaps::ConfigMap configMap_) : configMap(configMap_)
                {
                    if (configMap.hasKey("name")
                        && configMap.hasKey("opening_width") && configMap.hasKey("opening_height"))
                    {
                        name_ = configMap["name"].toString();
                        openingWidth = configMap["opening_width"];
                        openingHeight = configMap["opening_height"];

                        // we avoid the value dublication
                        // delete the keys, since we stored their values as class parameters
                        configMap.erase("name");
                        configMap.erase("opening_width");
                        configMap.erase("opening_height");
                    }
                    else
                    {
                        LOG_ERROR_S << "The config map has no all required keys";
                        configMap.clear();
                    }
                }

                std::string getType() const override
                {
                    return "camera";
                }

                configmaps::ConfigMap configMap;

                double openingWidth;
                double openingHeight;

                configmaps::ConfigMap getFullConfigMap()
                {
                    configmaps::ConfigMap config;
                    config.append(configMap);
                    config["name"] = getName();
                    config["openingWidth"] = openingWidth;
                    config["openingHeight"] = openingHeight;
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
