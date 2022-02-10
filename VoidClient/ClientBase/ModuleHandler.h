#pragma once

#include <algorithm>

#define PI 3.14159265359 // 3.14159265359

#include "Modules/TestModule.h"
#include "Modules/Watermark.h"
#include "Modules/Killaura.h"
#include "Modules/Instabreak.h"
#include "Modules/CreativeFly.h"
#include "Modules/ViewModel.h"
#include "Modules/AntiImmobile.h"
#include "Modules/AntiLagBack.h"
#include "Modules/AntiVoid.h"
#include "Modules/AutoSneak.h"
#include "Modules/AutoSprint.h"
#include "Modules/AutoWalk.h"
#include "Modules/Bhop.h"
#include "Modules/BlockReach.h"
#include "Modules/CreativeFly.h"
#include "Modules/Criticals.h"
#include "Modules/FluxSwing.h"
#include "Modules/Freelook.h"
#include "Modules/HiveFly.h"
#include "Modules/Phase.h"
#include "Modules/Reach.h"
#include "Modules/Tracers.h"
#include "Modules/Velocity.h"
#include "Modules/Zoom.h"
#include "Modules/ArrayList.h"

class ModuleHandler {
public:
    std::vector<Module*> modules;

public:

    struct CompareArg { bool operator()(Module* mod1, Module* mod2) { return mod1->name < mod2->name; } };

    void InitModules() {
        _logf(L"[VoidClient]: Registering modules...\n");

        // How to know what module goes where !
        std::string combat = "Combat"; // pvp stuff
        std::string world = "World"; // world stuff
        std::string movement = "Movement"; // movements
        std::string visual = "Visual"; // visual effects
        std::string misc = "Misc"; // other

        modules.push_back(new Killaura(combat)); // add
        modules.push_back(new Criticals(combat)); // add
        modules.push_back(new Reach(combat)); // add
        modules.push_back(new Velocity(combat)); // add
        modules.push_back(new BlockReach(combat)); // add
        modules.push_back(new FluxSwing(combat)); // add

        modules.push_back(new Instabreak(world)); // add

        modules.push_back(new CreativeFly(movement)); // add
        modules.push_back(new AutoSneak(movement)); // add
        modules.push_back(new AutoSprint(movement)); // add
        modules.push_back(new AutoWalk(movement)); // add
        modules.push_back(new HiveFly(movement)); // add
        modules.push_back(new Phase(movement)); // add
        modules.push_back(new Bhop(movement)); // add
        modules.push_back(new AntiLagBack(movement)); // add
        modules.push_back(new AntiVoid(movement)); // add
        modules.push_back(new AntiImmobile(movement)); // add

        modules.push_back(new Watermark(visual));
        modules.push_back(new ViewModel(visual)); // add
        modules.push_back(new Freelook(visual)); // add
        modules.push_back(new Tracers(visual)); // add
        modules.push_back(new ArrayList(visual));
        modules.push_back(new Zoom(visual)); // add

        modules.push_back(new TestModule(misc));
        // Sort modules
        std::sort(modules.begin(), modules.end(), CompareArg());

        _logf(L"[VoidClient]: Registered modules!\n");
    }

    void FrameRender(RenderUtils* ctx) {
        for (auto mod : modules)
            if (mod->enabled) {
                mod->OnFrameRender(ctx);
            }
    }
};
