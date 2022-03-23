#ifndef TEST_RESOURCEHOLDER_H
#define TEST_RESOURCEHOLDER_H
#include <string>
#include <memory>
#include <unordered_map>
#include <cassert>
#include <stdexcept>

namespace MW
{
    template <typename Resource, typename Identifier>
    class ResourceHolder
    {
    public:
        void load(Identifier id, const std::string& path);
        Resource& get(Identifier id);
        const Resource& get(Identifier id) const;

    private:
        void insertResource(Identifier id, std::unique_ptr<Resource> resource);

    private:
        std::unordered_map<Identifier, std::unique_ptr<Resource>> resources;
    };

    template<typename Resource, typename Identifier>
    inline void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& path)
    {
        std::unique_ptr<Resource> resource = std::make_unique<Resource>();

        if (!resource->loadFromFile(path))
        {
            throw std::runtime_error("ResourceHolder loading error: path = " + path);
        }

        insertResource(id, std::move(resource));
    }

    template<typename Resource, typename Identifier>
    inline Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
    {
        auto found = resources.find(id);
        assert(found != resources.end());

        return *found->second;
    }

    template<typename Resource, typename Identifier>
    inline const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
    {
        auto found = resources.find(id);
        assert(found != resources.end());

        return *found->second;
    }

    template<typename Resource, typename Identifier>
    inline void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource)
    {
        auto inserted = resources.emplace(id, std::move(resource));
        assert(inserted.second);
    }
}


#endif