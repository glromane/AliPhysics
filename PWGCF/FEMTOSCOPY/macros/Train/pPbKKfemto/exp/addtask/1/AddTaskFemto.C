//=============================================================================
//
// *** AddTaskFemto.C ***
// ---train version ---
// This macro initialize a complete AnalysisTask object for femtoscopy.
//=============================================================================
//AliAnalysisTaskFemto *AddTaskFemto(TString configMacroName, TString containerName="femtolist", TString configMacroParameters="")
AliAnalysisTaskFemto *AddTaskFemto(TString configMacroName, TString containerName="femtolist", TString configMacroParameters="",Bool_t kGridConfig = kFALSE, TString userName = "", TString configFunName = "ConfigFemtoAnalysis")
{
// Creates a proton analysis task and adds it to the analysis manager.

  // A. Get the pointer to the existing analysis manager via the static access method.
  //==============================================================================
  AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
  if (!mgr) {
    Error("AddTaskFemto", "No analysis manager to connect to.");
    return NULL;
  }

  // B. Check the analysis type using the event handlers connected to the analysis
  //    manager. The availability of MC handler cann also be checked here.
  //==============================================================================
  if (!mgr->GetInputEventHandler()) {
    ::Error("AddTaskFemto", "This task requires an input event handler");
    return NULL;
  }
  TString type = mgr->GetInputEventHandler()->GetDataType(); // can be "ESD" or "AOD"
  cout << "Found " <<type << " event handler" << endl;

  // C. Create the task, add it to manager.
  //===========================================================================
//  gSystem->SetIncludePath("-I$ROOTSYS/include  -I./PWG2AOD/AOD -I./PWG2femtoscopy/FEMTOSCOPY/AliFemto -I./PWG2femtoscopyUser/FEMTOSCOPY/AliFemtoUser -I$ALICE_PHYSICS/include");

  if (TProofMgr::GetListOfManagers()->GetEntries()) {
//     if (dynamic_cast<TProofLite *> gProof) {
//       char *macrocommand[10000];
//       sprintf(macrocommand, ".L %s", configMacroName);
//       gProof->Exec(macrocommand);
//     }
//     else
    gProof->Load(configMacroName);
  }
  //  gROOT->LoadMacro("ConfigFemtoAnalysis.C++");

  //AliAnalysisTaskFemto *taskfemto = new AliAnalysisTaskFemto("TaskFemto","$ALICE_PHYSICS/"+configMacroName,configMacroParameters,kFALSE);
  AliAnalysisTaskFemto *taskfemto;
  if(kGridConfig)
    {
      taskfemto = new AliAnalysisTaskFemto("TaskFemto",configMacroName,configMacroParameters,kFALSE,kTRUE,userName,configFunName);
    }
  else
    {
      taskfemto = new AliAnalysisTaskFemto("TaskFemto","$ALICE_PHYSICS/"+configMacroName,configMacroParameters,kFALSE,kFALSE,userName,configFunName);
    }

  //taskfemto->SelectCollisionCandidates(AliVEvent::kINT7);

  mgr->AddTask(taskfemto);

  // D. Configure the analysis task. Extra parameters can be used via optional
  // arguments of the AddTaskXXX() function.
  //===========================================================================

  // E. Create ONLY the output containers for the data produced by the task.
  // Get and connect other common input/output containers via the manager as below
  //==============================================================================
  TString outputfile = AliAnalysisManager::GetCommonFileName();
  outputfile += ":PWG2FEMTO";
  //AliAnalysisDataContainer *cout_femto  = mgr->CreateContainer("ER_woSDD",TList::Class(),AliAnalysisManager::kOutputContainer,outputfile);
  AliAnalysisDataContainer *cout_femto  = mgr->CreateContainer(containerName,TList::Class(),AliAnalysisManager::kOutputContainer,outputfile);

   mgr->ConnectInput(taskfemto, 0, mgr->GetCommonInputContainer());
   mgr->ConnectOutput(taskfemto, 0, cout_femto);

   // Return task pointer at the end
   return taskfemto;
}
