#include "FireEmblemEditor.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"

IMPLEMENT_GAME_MODULE(FFireEmblemEditorModule, FireEmblemEditor);

DEFINE_LOG_CATEGORY(FireEmblemEditor)

#define LOCTEXT_NAMESPACE "FireEmblemEditor"

void FFireEmblemEditorModule::StartupModule()
{
    UE_LOG(FireEmblemEditor, Warning, TEXT("FireEmblemEditor: Module Started"));
}

void FFireEmblemEditorModule::ShutdownModule()
{
    UE_LOG(FireEmblemEditor, Warning, TEXT("FireEmblemEditor: Module Ended"));
}

#undef LOCTEXT_NAMESPACE