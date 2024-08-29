
#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#include <base-logging/Logging.hpp>
#include <configmaps/ConfigSchema.hpp>

#include "TypeCreatorInterface.hpp"

namespace envire
{
    namespace types
    {
        class TypeCreatorFactory
        {
            typedef std::shared_ptr<TypeCreatorInterface> CreatorPtr;
            typedef std::unordered_map<std::string, CreatorPtr> CreatorMap;
            typedef std::unordered_map<std::string, configmaps::ConfigSchema> ConfigSchemaMap;

            public:
                // TODO: if the className is already registered
                static void registerTypeCreator(std::string className, CreatorPtr &creator);

                static envire::core::ItemBase::Ptr createItem(std::string className, configmaps::ConfigMap &configmap);

                static bool getCreator(std::string className, CreatorPtr& creator);

                static bool getConfigSchema(const std::string& className, configmaps::ConfigSchema& configSchema);

            private:
                static void registerConfigSchema(const std::string& className);
                static std::string setupConfigSchemaPath(const std::string& className);
                static CreatorMap& getCreatorMap();
                static ConfigSchemaMap& getConfigSchemaMap();
        };
    }
}
