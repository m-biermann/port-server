//
// Created by max on 8/24/20.
//

#include <mabiphmo/portServer/main.h>
#include <mabiphmo/ioc-server/main.h>
#include "construction/AppBuilder.h"

void Configure(mabiphmo::ioc_server::construction::IAppBuilder &baseBuilder)
{
	mabiphmo::portServer::construction::AppBuilder builder(baseBuilder);
	Configure(builder);
}