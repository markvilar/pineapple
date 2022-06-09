#pragma once

#include <typeinfo>
#include <typeindex>
#include <type_traits>

namespace pineapple
{

template <typename Header, typename Data>
struct Message
{
    using HeaderType = Header;
    using DataType = Data;

    Header header{};
    Data data{};
};

template <typename Archive, typename Header, typename Data>
auto serialize(Archive& archive, Message<Header, Data>& message)
{
    archive(message.header, message.data);
}

template <typename Archive, typename Header, typename Data>
auto serialize(Archive& archive, const Message<Header, Data>& message)
{
    archive(message.header, message.data);
}

}; // namespace pineapple
