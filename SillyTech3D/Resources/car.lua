old_t = 0.0
playing = false

function Update()
	t = Time():GetTime()/2.5
	dt = Time():GetDeltaTime()
	--t = math.sin(ms)
	car = GetActorByName("Car")
	if playing == false then
		car:GetAudioComponent(false):Play()
		playing = true
	end
	
	trans = car:GetTransform()
	pos = trans:GetPosition()
	pos.x = 4000.0*math.sin(t)
	pos.z = 4000.0*math.cos(t)
	--newPos = pos + vec3(100.0*math.sin(t),0.0,100.0*math.cos(t))
	trans:SetPosition(pos)
	--trans:Rotate(Time():GetDeltaTime()*-360.0/(2.0*math.pi), trans:Up())
	--trans:SetRotation((math.sin(t)+1.0)*90.0, trans:Up())
	trans:SetRotation(((t/(2.0*math.pi)) %1.0)*360.0 + 90, trans:Up())
	
	old_t = t
end