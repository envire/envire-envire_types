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
            class RaySensor : public EnvireTypeBase
            {
            public:
                RaySensor() {}

                RaySensor(const configmaps::ConfigMap& configMap) : EnvireTypeBase(configMap)
                {
                    if (configMap_.hasKey("name")
                        && configMap_.hasKey("max_distance")
                        && configMap_.hasKey("opening_width"))
                    {
                        name_ = configMap_["name"].toString();
                        maxDistance = configMap_["max_distance"];
                        openingWidth = configMap_["opening_width"];

                        // we avoid the value dublication
                        // delete the keys, since we stored their values as class parameters
                        configMap_.erase("name");
                        configMap_.erase("max_distance");
                        configMap_.erase("opening_width");
                    }
                    else
                    {
                        LOG_ERROR_S << "The config map has no all required keys";
                        configMap_.clear();
                    }
                }

                std::string getType() const override
                {
                    return "ray";
                }

                double maxDistance;
                double openingWidth;

                configmaps::ConfigMap getFullConfigMap() const override
                {
                    configmaps::ConfigMap config;
                    config.append(configMap_);
                    config["name"] = getName();
                    config["max_distance"] = maxDistance;
                    config["opening_width"] = openingWidth;
                    return config;
                }

                /**Grants access to boost serialization */
                friend class boost::serialization::access;

                /**Serializes the members of this class*/
                template <typename Archive>
                void serialize(Archive &ar, const unsigned int version)
                {
                    throw std::runtime_error("envire::types::RaySensor serialize not implemented");
                }
            };
        }
    }
}
