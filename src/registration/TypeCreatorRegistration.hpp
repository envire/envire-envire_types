#pragma once

#include "TypeCreatorFactory.hpp"

#include <iostream>


#include <cstdio>

namespace envire {

    namespace types {


        #define ENVIRE_TYPE_CREATOR_REGISTRATION(_datatype) \
        ENVIRE_TYPE_CREATOR_REGISTRATION_INTERNAL(_datatype, __COUNTER__)

        #define ENVIRE_TYPE_CREATOR_REGISTRATION_INTERNAL(_datatype, _unique_id) \
        ENVIRE_TYPE_CREATOR_REGISTRATION_INTERNAL_EXPANDED(_datatype, _unique_id)

        #define ENVIRE_TYPE_CREATOR_REGISTRATION_INTERNAL_EXPANDED(_datatype, _unique_id) \
        class TypeCreator ## _unique_id : public envire::types::TypeCreatorInterface \
        { \
        public: \
            virtual envire::core::ItemBase::Ptr createItem(configmaps::ConfigMap &configmap) \
            { \
                _datatype obj(configmap); \
                envire::core::ItemBase::Ptr ptr = envire::core::ItemBase::Ptr(new envire::core::Item<_datatype>(obj)); \
                return ptr; \
            } \
            virtual std::string getClassName() \
            { \
                return std::string(#_datatype); \
            } \
        }; \
        static envire::types::TypeCreatorRegistration<TypeCreator ## _unique_id> reg ## _unique_id(#_datatype);

        template<typename T>
        class TypeCreatorRegistration
        {
        public:
            TypeCreatorRegistration(const std::string& className)
            {
                std::shared_ptr<TypeCreatorInterface> ptr(new T);
                TypeCreatorFactory::registerTypeCreator(className, ptr);
            }
        };
    }
}
