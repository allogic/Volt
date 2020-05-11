#include <VoltModule.h>

Volt::Module::Module() {}
Volt::Module::~Module() {}

int Volt::Module::OnUpdate() { return 0; }
int Volt::Module::OnRender() const { return 0; }

