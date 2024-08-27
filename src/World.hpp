#pragma once

#include "EnvireTypeBase.hpp"

#include <base/Eigen.hpp>
#include <configmaps/ConfigMap.hpp>
#include <envire_core/plugin/Plugin.hpp>

namespace envire
{
    namespace types
    {
        class World : public EnvireTypeBase
        {
        public:
            World() {}
            World(configmaps::ConfigMap configMap_) : EnvireTypeBase(configMap_)
            {
                name_ = configMap["name"].toString();
                prefix = configMap["prefix"].toString();

                // we avoid the value dublication
                // delete the keys, since we stored their values as class parameters
                configMap.erase("name");
                configMap.erase("prefix");
            }

            std::string getType() const override
            {
                return "world";
            }

            std::string prefix;

            configmaps::ConfigMap getFullConfigMap() const override
            {
                configmaps::ConfigMap config;
                config.append(configMap);
                config["name"] = getName();
                config["type"] = getType();
                config["prefix"] = prefix;
                return config;
            }

            /**Grants access to boost serialization */
            friend class boost::serialization::access;

            /**Serializes the members of this class*/
            template <typename Archive>
            void serialize(Archive &ar, const unsigned int version)
            {
                throw std::runtime_error("envire::types::World::serialize not implemented");
            }
        };
    }
}

