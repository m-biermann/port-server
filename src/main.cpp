//
// Created by max on 8/24/20.
//

#include <mabiphmo/iocServer/main.h>
#include <mabiphmo/portServer/main.h>
#include "construction/AppBuilder.h"

void Configure(mabiphmo::iocServer::construction::IAppBuilder &baseBuilder)
{
	mabiphmo::portServer::construction::AppBuilder builder(baseBuilder);
	Configure(builder);
}