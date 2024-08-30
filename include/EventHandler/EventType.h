#ifndef ENUM_EVENT_TYPE
#define ENUM_EVENT_TYPE

enum EventType{
    EVENT_ON_CLICK_DOWN,
    EVENT_ON_CLICK_UP,
    EVENT_ON_HOVER_ENTER,
    EVENT_ON_HOVER_LEAVE
};

NLOHMANN_JSON_SERIALIZE_ENUM(EventType,{
    {EVENT_ON_CLICK_DOWN, "onclickdown"},
    {EVENT_ON_CLICK_UP, "onclickup"},
    {EVENT_ON_HOVER_ENTER, "onhoverenter"},
    {EVENT_ON_HOVER_LEAVE, "onhoverleave"}
});

#endif