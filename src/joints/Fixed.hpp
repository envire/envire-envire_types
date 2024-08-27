#pragma once

#include "../EnvireTypeBase.hpp"

#include <string>
#include <boost/serialization/access.hpp>
#include <configmaps/ConfigMap.hpp>
#include <base-logging/Logging.hpp>

namespace envire
{
    namespace types
    {
        namespace joints
        {
            class Fixed: public EnvireTypeBase
            {
            public:
                Fixed() {}

                Fixed(configmaps::ConfigMap configMap_) : configMap(configMap_)
                {
                    if (configMap.hasKey("name"))
                    {
                        name_ = configMap["name"].toString();

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

                std::string getType() const override
                {
                    return "fixed";
                }

                configmaps::ConfigMap configMap;

                configmaps::ConfigMap getFullConfigMap()
                {
                    configmaps::ConfigMap config;
                    config.append(configMap);
                    config["name"] = getName();
                    config["type"] = getType();
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
