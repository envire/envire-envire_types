
#include "TypeCreatorFactory.hpp"

namespace envire
{
    namespace types
    {
        // TODO: if the className is already registered
        void TypeCreatorFactory::registerTypeCreator(std::string className, CreatorPtr &creator)
        {
            getCreatorMap()[className] = creator;
        }

        envire::core::ItemBase::Ptr TypeCreatorFactory::createItem(std::string className, configmaps::ConfigMap &configmap)
        {
            CreatorPtr creator;
            if (getCreator(className, creator) == false) {
                LOG_ERROR_S << "No type creator is registered for the type " << className;
                return NULL;
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

        TypeCreatorFactory::CreatorMap& TypeCreatorFactory::getCreatorMap()
        {
            static CreatorMap creators;
            return creators;
        }
    }
}
