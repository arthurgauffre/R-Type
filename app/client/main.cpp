/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <CoreModule.hpp>
#include <r-type/IEntity.hpp>

int main(void) 
{
    // unique  ptr to CoreModule
    std::unique_ptr<rtype::CoreModule> coreModule = std::make_unique<rtype::CoreModule>();

    // hello world coreModule
    coreModule->helloWorld();
    coreModule->loadEntityConstructor();
    std::shared_ptr<entity::IEntity> entity = coreModule->entityConstructor->getInstance("createEntity", 1);
    // print entity id
    std::cout << entity->getID() << std::endl;
    return 0;
}
