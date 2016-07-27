#include "global.h"

World* world=NULL;

void InitWorld() {
	world=new World();
}

void ReleaseWorld() {
	delete world;
}

