#include "ResourceHolder.hpp"

using namespace gameResources;

gameResources::ResourceHolder& gameResources::ResourceHolder::get()
{
    static ResourceHolder holder;
    return holder;
}

