#include "TypeCreatorFactory.hpp"

#include <string>
#include <sstream>
#include <vector>
#include <configmaps/ConfigMap.hpp>


namespace envire
{
    namespace types
    {
        // TODO: if the className is already registered
        void TypeCreatorFactory::registerTypeCreator(std::string className, CreatorPtr &creator)
        {
            getCreatorMap()[className] = creator;

            registerConfigSchema(className);
        }

        void TypeCreatorFactory::registerConfigSchema(const std::string& className)
        {
            auto configSchemaPath = setupConfigSchemaPath(className);
            try
            {
                auto configSchema = configmaps::ConfigSchema{configmaps::ConfigMap::fromYamlFile(configSchemaPath)};
                getConfigSchemaMap()[className] = configSchema;
            }
            catch (std::runtime_error e)
            {
                LOG_ERROR_S << "Could not load config schema for type " << className << ": " << e.what();
            }
        }

        envire::core::ItemBase::Ptr TypeCreatorFactory::createItem(std::string className, configmaps::ConfigMap &configmap)
        {
            CreatorPtr creator;
            if (getCreator(className, creator) == false) {
                LOG_ERROR_S << "No type creator is registered for the type " << className;
                return NULL;
            }

            configmaps::ConfigSchema configSchema;
            if (!getConfigSchema(className, configSchema))
            {
                LOG_WARN_S << "No config schema registered for the type " << className;
            }
            else if(!configSchema.validate(configmap))
            {
                // TODO: Handle name not being a string
                const auto nameString = configmap.hasKey("name") ? std::string{"; item name: "} + configmap["name"].toString() : std::string{""};
                LOG_ERROR_S << "Invalid configuration for type " << className << nameString;
            }

            return creator->createItem(configmap);
        }

        bool TypeCreatorFactory::getCreator(std::string className, CreatorPtr& creator)
        {
            CreatorMap::iterator it = getCreatorMap().find(className);
            if(it != getCreatorMap().end())
            {
                creator = it->second;
                return true;
            }
            return false;
        }

        bool TypeCreatorFactory::getConfigSchema(const std::string& className, configmaps::ConfigSchema& configSchema)
        {
            auto configSchemaMap = getConfigSchemaMap();
            auto configSchemaItr = configSchemaMap.find(className);
            if (configSchemaItr == std::end(configSchemaMap))
            {
                return false;
            }

            configSchema = configSchemaItr->second;
            return true;
        }

        std::string TypeCreatorFactory::setupConfigSchemaPath(const std::string& className)
        {
            auto split = [](const std::string& s, char delimiter = ':')
            {
                std::vector<std::string> result;
                auto ss = std::stringstream{s};
                std::string item;
                while (std::getline(ss, item, delimiter))
                {
                    result.push_back(item);
                }
                return result;
            };

            const auto exploded = split(className);
            const auto len = exploded.size();
            const auto basePath = std::string{SCHEMA_PATH};

            return basePath + "/" + (len > 5 ? exploded[len-3] + "/" : "") + exploded[len-1] + "_schema.yml";
        }

        TypeCreatorFactory::CreatorMap& TypeCreatorFactory::getCreatorMap()
        {
            static CreatorMap creators;
            return creators;
        }

        TypeCreatorFactory::ConfigSchemaMap& TypeCreatorFactory::getConfigSchemaMap()
        {
            static ConfigSchemaMap configSchemas;
            return configSchemas;
        }
    }
}
