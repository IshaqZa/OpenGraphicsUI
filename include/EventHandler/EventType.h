#ifndef ENUM_EVENT_TYPE
#define ENUM_EVENT_TYPE

enum EventType{
    EVENT_ON_CLICK
};

NLOHMANN_JSON_SERIALIZE_ENUM(EventType,{
    {EVENT_ON_CLICK, "onclick"}
});

#endif