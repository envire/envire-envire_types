
#pragma once

#include <string>
#include <configmaps/ConfigMap.hpp>
#include <envire_core/items/Item.hpp>

namespace envire
{
    namespace types
    {
        class TypeCreatorInterface
        {
            public:
                virtual ~TypeCreatorInterface() {};

                virtual envire::core::ItemBase::Ptr createItem(configmaps::ConfigMap &configmap) = 0;

                virtual std::string getClassName() = 0;
        };
    }
}
