#pragma once

#include <base/Eigen.hpp>
#include <configmaps/ConfigMap.hpp>
#include <envire_core/plugin/Plugin.hpp>

namespace envire
{
    namespace types
    {
        struct World
        {
            World() {}
            World(configmaps::ConfigMap configMap) {
                name = configMap["name"].toString();
                prefix = configMap["prefix"].toString();

                // we avoid the value dublication
                // delete the keys, since we stored their values as class parameters
                configMap.erase("name");
                configMap.erase("prefix");

                this->configMap = configMap;
            }

            std::string name;
            const std::string& getName() const
            {
                return name;
            }
            std::string prefix;
            const std::string& getPrefix() const
            {
                return prefix;
            }
            static inline std::string const type = "world";
            configmaps::ConfigMap configMap;

            configmaps::ConfigMap getFullConfigMap() {
                configmaps::ConfigMap config;
                config.append(configMap);
                config["name"] = name;
                config["type"] = type;
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

