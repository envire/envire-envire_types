
#pragma once

#include <string>
#include <map>
#include <memory>

#include <base-logging/Logging.hpp>

#include "TypeCreatorInterface.hpp"

namespace envire
{
    namespace types
    {
        class TypeCreatorFactory
        {
            typedef std::shared_ptr<TypeCreatorInterface> CreatorPtr;
            typedef std::map<std::string, CreatorPtr> CreatorMap;

            public:
                // TODO: if the className is already registered
                static void registerTypeCreator(std::string className, CreatorPtr &creator);

                static envire::core::ItemBase::Ptr createItem(std::string className, configmaps::ConfigMap &configmap);

                static bool getCreator(std::string className, CreatorPtr& creator);

            private:
                static CreatorMap& getCreatorMap();
        };
    }
}
