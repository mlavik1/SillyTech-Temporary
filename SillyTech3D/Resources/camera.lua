mPos = vec2(0.0,0.0);
wheel = vec2(0.0,0.0);

function Update()
	
	ac = GetActorByName("CamActor")
	if ac == nil then
		PrintText("Actor does not exist")
	end
	trans = ac:GetTransform()
	vc = trans:GetPosition()
	
	mPosNew = Input():GetMousePosition()
	if Input():GetKey("lctrl") then
		xDiff = mPos.x-mPosNew.x
		if xDiff ~= 0.0 then
			trans:Rotate(xDiff*0.5,vec3(0.0,1.0,0.0)) -- use global Y-axis for camera rotation
		end
		yDiff = mPos.y-mPosNew.y
		if yDiff ~= 0.0 then
			trans:Rotate(yDiff*0.5,trans:Right())
		end
				
	end
	
	wheel = wheel + Input():GetMouseWheel()
	if wheel.y ~= 0.0 then
		vc = vc + trans:Forward() * wheel.y
		trans:SetPosition(vc)
	end
	
	--if Input():GetMouseDown(1) then
	--	vc = vec3(0.0,0.0,0.0)
	--	trans:SetPosition(vc)
	--end
	fps = Time():GetFramesPerSecond()
	if Input():GetKeyDown("f") then
		print("FPS: " .. fps)
	end
	
	if Input():GetKeyDown("t") then
		allmr = GetActorByName("Tidus"):GetMeshRenderComponents(true)
		for mr in allmr do
			mr:GetMaterial():GetShaderProgram():SetInt("test",1)
		end
	end
	
	if Input():GetKeyDown("r") then
		RecompileShaders()
	end
	if Input():GetKeyDown("a") then
		GetActorByName("Tidus"):GetAudioComponent(true):Play()
	end
	if Input():GetKeyDown("m") then
		print("Playing music")
		GetActorByName("AudioActor"):GetAudioComponent(true):Play()
	end
	if Input():GetKeyDown("p") then
		print("TEST")
		ppp = NewPhysicsComponent()
		GetActorByName("Tidus"):AttachComponent(ppp)
	end
	
	sbt = GetActorByName("Skybox"):GetTransform()
	sbp = sbt:GetPosition()
	sbp = vec3(vc.x, sbp.y, vc.z)
	sbt:SetPosition(sbp)
	
	mPos = mPosNew
	
end