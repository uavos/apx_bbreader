#include "bbreaderplugin.h"

#include "bbreaderform.h"

BbReaderPlugin::BbReaderPlugin()
{
}

QObject *BbReaderPlugin::createControl()
{
    return new BbReaderForm();
}

int BbReaderPlugin::flags()
{
    return WidgetPlugin;
}
