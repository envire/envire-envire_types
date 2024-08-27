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

            World(const configmaps::ConfigMap& configMap) : EnvireTypeBase(configMap)
            {
                name_ = configMap_["name"].toString();
                prefix_ = configMap_["prefix"].toString();

                // we avoid the value dublication
                // delete the keys, since we stored their values as class parameters
                configMap_.erase("name");
                configMap_.erase("prefix");
            }

            std::string getType() const override
            {
                return "world";
            }

            configmaps::ConfigMap getFullConfigMap() const override
            {
                configmaps::ConfigMap config;
                config.append(configMap_);
                config["name"] = getName();
                config["type"] = getType();
                config["prefix"] = getPrefix();
                return config;
            }

            const std::string& getPrefix() const
            {
                return prefix_;
            }

            /**Grants access to boost serialization */
            friend class boost::serialization::access;

            /**Serializes the members of this class*/
            template <typename Archive>
            void serialize(Archive &ar, const unsigned int version)
            {
                throw std::runtime_error("envire::types::World::serialize not implemented");
            }

        private:
            std::string prefix_;
        };
    }
}

