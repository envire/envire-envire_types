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
            class CameraSensor : public EnvireTypeBase
            {
            public:
                CameraSensor() {}

                CameraSensor(configmaps::ConfigMap configMap) : EnvireTypeBase(configMap)
                {
                    if (configMap_.hasKey("name")
                        && configMap_.hasKey("opening_width") && configMap_.hasKey("opening_height"))
                    {
                        name_ = configMap_["name"].toString();
                        openingWidth = configMap_["opening_width"];
                        openingHeight = configMap_["opening_height"];

                        // we avoid the value dublication
                        // delete the keys, since we stored their values as class parameters
                        configMap_.erase("name");
                        configMap_.erase("opening_width");
                        configMap_.erase("opening_height");
                    }
                    else
                    {
                        LOG_ERROR_S << "The config map has no all required keys";
                        configMap_.clear();
                    }
                }

                std::string getType() const override
                {
                    return "camera";
                }

                double openingWidth;
                double openingHeight;

                configmaps::ConfigMap getFullConfigMap() const override
                {
                    configmaps::ConfigMap config;
                    config.append(configMap_);
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
