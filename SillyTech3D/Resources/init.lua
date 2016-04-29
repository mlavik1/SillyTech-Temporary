-- *************************************************
-- *****S C E N E   I N I T I A L I S A T I O N*****
-- *************************************************

-- Skybox
skybox = CreateActorFromModel("Skybox", "Resources/Skybox/Skybox.obj")
skybox:GetTransform():SetScale(vec3(30000.0, 30000.0, -30000.0))
skybox:GetTransform():SetPosition(vec3(0.0,-5000.0,0.0))
skybox:GetMeshRenderComponent(true):GetMaterial():GetShaderProgram():SetInt("no_lighting",1)

-- Main Camera
camActor = NewActor()
camActor:SetName("CamActor")
camComp = NewCameraComponent()
camActor:AttachComponent(camComp)
camera_script = NewLuaScriptComponent()
camera_script:SetScript("Resources/camera.lua")
camActor:AttachComponent(camera_script)

child = NewActor()
camActor:AddChild(child)
childCam = NewCameraComponent()
childCam:SetViewport(Viewport(0.0,0.0,0.3,0.3))
child:AttachComponent(childCam)

audioActor = NewActor()
audioActor:SetName("AudioActor")
bgm = NewAudioComponent("Resources/Audio/metro.wav")
audioActor:AttachComponent(bgm)

-- Car
--car = CreateActorFromModel("Car", "Resources/Model/bmw/BMW_M3_GTR.obj")
car = CreateActorFromModel("Car", "Resources/Model/Ferrari/ferrari-f1-race-car.obj")
car:GetTransform():SetPosition(vec3(-80.0, -10.0, -200.0))
--car:GetTransform():SetScale(vec3(0.10, 0.10, 0.10))
car:GetTransform():SetScale(vec3(110.10, 110.10, 110.10))
car_script = NewLuaScriptComponent()
car_script:SetScript("Resources/car.lua")
car_audio = NewAudioComponent("Resources/Audio/engine4.wav")
car_audio:Set3DSound(true)
car_audio:SetLooping(true)
car:AttachComponent(car_audio)
car:AttachComponent(car_script)

-- Terrain
bergen = CreateActorFromModel("Bergen", "Resources/Heightmap/Heightmap.obj")
bergen:GetTransform():SetPosition(vec3(-6750.0, -550.0, -8950.0))
bergen:GetTransform():SetScale(vec3(1.0, 1.0, 1.0))
bergen_physics = NewPhysicsComponent()
bergen:AttachComponent(bergen_physics)
bergen_physics:SetKinematic(true)

-- Tidus
tidus = CreateActorFromModel("Tidus", "Resources/tidus/model.obj")
tidus:GetTransform():SetScale(vec3(0.01, 0.01, 0.01))
tidus:GetTransform():SetPosition(vec3(-20.0, 100.0, -150.0))
tidus_script = NewLuaScriptComponent()
tidus_script:SetScript("Resources/tidus_move.lua")
tidus:AttachComponent(tidus_script)
ppp = NewPhysicsComponent()
tidus:AttachComponent(ppp)
a = NewAudioComponent("Resources/Audio/engine4.wav")
a:Set3DSound(true)
a:SetLooping(true)
tidus:AttachComponent(a)


light = NewActor()
light:SetName("Light")
light:GetTransform():SetPosition(vec3(-300.0, 1000.0, 100.0))
light_comp = NewLightComponent()
light_comp:SetAmbientColour(vec3(0.05,0.05,0.05))
light_comp:SetDiffuseColour(vec3(0.8,0.8,0.8))
light_comp:SetSpecularColour(vec3(0.55,0.55,0.55))
light:AttachComponent(light_comp)



--car = CreateActorFromModel("Car", "Resources/Model/Natla/natla car.obj")


--camComp->SetViewport(Viewport(0.0f,0.0f,1.0f,1.0f));
--camActor->AttachComponent(camComp);
--ActorManager::Instance()->AttachActor(camActor);
