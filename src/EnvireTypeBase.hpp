#pragma once

#include <string>
#include <configmaps/ConfigMap.hpp>


namespace envire
{
    namespace types
    {
        class EnvireTypeBase
        {
        public:
            EnvireTypeBase() : name_{"NOT SET"} {}
            EnvireTypeBase(const std::string& name) : name_{name} {}
            EnvireTypeBase(const configmaps::ConfigMap& configMap) : configMap_{configMap} {}
            virtual ~EnvireTypeBase() = default;


            virtual std::string getType() const = 0;
            virtual configmaps::ConfigMap getFullConfigMap() const = 0;

            const std::string& getName() const
            {
                return name_;
            }

        protected:
            configmaps::ConfigMap configMap_;
            std::string name_;
        };
    }
}
