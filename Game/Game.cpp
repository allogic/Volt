#include <Types.h>
#include <Core.h>
#include <Module.h>

#include <iostream>

class CGame
  : public Volt::CModule
{
public:
  CGame() = default;
  virtual ~CGame() = default;

  inline const char*  WindowTitle() const override { return "Game"; };
  inline const s32    WindowWidth() const override { return 1280; };
  inline const s32    WindowHeight() const override { return 720; };

  inline s32          OnUpdate() override { return 0; }
  inline s32          OnRender() const override { return 0; }
};

VOLT_MAKE_MODULE(CGame);