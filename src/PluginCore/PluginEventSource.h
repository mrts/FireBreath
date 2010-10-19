/**********************************************************\
Original Author: Richard Bateman (taxilian)

Created:    Oct 19, 2009
License:    Dual license model; choose one of two:
            New BSD License
            http://www.opensource.org/licenses/bsd-license.php
            - or -
            GNU Lesser General Public License, version 2.1
            http://www.gnu.org/licenses/lgpl-2.1.html

Copyright 2009 PacketPass, Inc and the Firebreath development team
\**********************************************************/

#pragma once
#ifndef H_FB_PLUGINEVENTSOURCE
#define H_FB_PLUGINEVENTSOURCE

#include <vector>
#include <typeinfo>

namespace FB {

    class PluginEventSink;
    class PluginEvent;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class  PluginEventSource
    ///
    /// @brief  Base class for any object, such as BrowserStream or PluginWindow, that needs to fire
    /// 		events to a PluginEventSink object (such as a PluginCore derived plugin class) 
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class PluginEventSource
    {
    public:
        PluginEventSource();
        virtual ~PluginEventSource();

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @fn virtual void PluginEventSource::AttachObserver(PluginEventSink*)
        ///
        /// @brief  Attach a PluginEventSink to receive events
        ///
        /// @param  sink PluginEventSink to attach
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void AttachObserver(PluginEventSink* sink);

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @fn virtual void PluginEventSource::DetachObserver(PluginEventSink* sink)
        ///
        /// @brief  Detach a PluginEventSink so it no longer receives events from this source
        ///
        /// @param  sink PluginEventSink to attach
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void DetachObserver(PluginEventSink* sink);

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @fn virtual bool PluginEventSource::SendEvent(PluginEvent* evt)
        ///
        /// @brief  Sends an event to all attached sinks
        ///
        /// @param  evt The event to send
        ///
        /// @return true if the event was handled, false if it was not
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool SendEvent(PluginEvent* evt);

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @fn template <class T> T* PluginEventSource::get_as()
        ///
        /// @brief  Templated convenience function for performing a dynamic cast of this object
        /// 		
        /// @code
        /// 	 PluginWindow* wnd = evtSource->get_as<PluginWindow>();
        /// @endcode
        ///
        /// @exception  std::bad_cast   Thrown when bad cast. 
        ///
        /// @return null if it fails, else T* 
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        template <class T>
        T* get_as()
        {
            T* tmp = dynamic_cast<T*>(this);
            if (!tmp)
                throw std::bad_cast();
            return tmp;
        }

    protected:

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @typedef    std::vector<PluginEventSink*> ObserverMap
        ///
        /// @brief  Defines an alias representing the observer .
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        typedef std::vector<PluginEventSink*> ObserverMap; 
        ObserverMap m_observers; /// List of attached observers
    };
};

#endif
