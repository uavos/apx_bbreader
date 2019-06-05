#ifndef BBREADERPLUGIN_H
#define BBREADERPLUGIN_H

#include "ApxPluginInterface.h"

class BbReaderPlugin: public ApxPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.uavos.gcs.ApxPluginInterface/1.0")
    Q_INTERFACES(ApxPluginInterface)
public:
    BbReaderPlugin();
    QObject *createControl();
    int flags();
};

#endif // BBREADERPLUGIN_H
