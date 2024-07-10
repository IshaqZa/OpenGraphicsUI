#ifndef ENUM_EVENT_TYPE
#define ENUM_EVENT_TYPE

enum EventType{
    EVENT_ON_CLICK,
    EVENT_ON_HOVER
};

NLOHMANN_JSON_SERIALIZE_ENUM(EventType,{
    {EVENT_ON_CLICK, "onclick"},
    {EVENT_ON_HOVER, "onhover"}
});

#endif