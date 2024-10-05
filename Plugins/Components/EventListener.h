#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

// local project headers
// ----------------------
#include "CommonTypes.h"

// standard C/C++ headers
// ----------------------
#include <vector>

class EventListener
{
public:
    enum ResponseType
    {
        NoResponse,
        AuthenticationResponse,
        FileResponse,
        DirectoryResponse,
        UserResponse
    };

    EventListener() = default;

    inline BuildRequest getRequestEvent() const { return m_requestEvent; }

    inline ResponseType getResponseEvent() const { return m_responseEvent; }

    inline bool hasEvents() { return m_requestEvent != BuildRequest::NoRequest; }

    inline void notifyEvent(BuildRequest event)
    {
        m_requestEvent = event;
    }

    inline void clearCurrentEvent()
    {
        m_requestEvent = BuildRequest::NoRequest;
    }

    // DE AICI NEORDONATE

    void setIsUserLoggedIn(bool isUserLoggedIn) { m_isUserLoggedIn = isUserLoggedIn; }

    void listen();

//    inline bool isEventTriggered(RequestType event);
    inline bool isEventTriggered(BuildRequest requestType) { return m_requestEvent == requestType; }

private:
    BuildRequest m_requestEvent;
    ResponseType m_responseEvent;
    std::vector<BuildRequest> m_activeEvents;
    bool m_isUserLoggedIn;
};

#endif // EVENT_LISTENER_H
