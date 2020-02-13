#ifndef BBREADERPLUGIN_H
#define BBREADERPLUGIN_H

#include "App/PluginInterface.h"

class BbReaderPlugin: public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.uavos.gcs.PluginInterface/1.0")
    Q_INTERFACES(PluginInterface)
public:
    BbReaderPlugin();
    QObject *createControl();
    int flags();
    QString title();
};



#endif // BBREADERPLUGIN_H
