#include <TruckersMP/TruckersMP.hxx>

#include <memory>

static std::unique_ptr< TruckersMP::Session > g_session;

TMP_EXPORT bool TMP_API truckersmp_init( const TruckersMP_Host *host, TruckersMP_PluginDesc *desc )
{
    // Identify yourself. The client shows this in its plugin list and logs.
    TruckersMP::PluginInfo info;
    info.m_name = "TruckersMP Trivia";
    info.m_author = "Penguin";
    info.m_version = "1.0.0";
    info.m_description = "Trivia will randomly pop-up as a notification, answer the question and be rewarded!";
    TruckersMP::FillPluginDesc( desc, info );

    // Establish the SDK connection. This declares the SDK version your plugin
    // was built against and acquires every available module.
    g_session = TruckersMP::Session::Create( host );
    if( g_session == nullptr )
    {
        // The client refused the session (for example, the plugin was built
        // against a newer SDK than the client supports). Returning false
        // refuses the load; the client unloads the DLL without calling
        // truckersmp_shutdown.
        return false;
    }

    g_session->Core().LogMessage( TruckersMP::LogLevel::Info, "Hello from my first plugin!" );

    g_session->Network().OnConnected.Register( []
    {
        g_session->UserInterface().ShowNotification(
            TruckersMP::NotificationType::Success, "Connected. Happy trucking!" );
    } );

    return true;
}

TMP_EXPORT void TMP_API truckersmp_shutdown( void )
{
    // Destroying the session unregisters every listener.
    g_session.reset();
}
