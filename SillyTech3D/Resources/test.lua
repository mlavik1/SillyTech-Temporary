function Update()
	
	ac = GetActorByName("")
	if ac == nil then
		--PrintText("nil")
	else
		ac:SetName("Matias")
		PrintText(ac:GetName())
	end
	
	ac = GetActorByName("Matias")
	if ac == nil then
		PrintText("NEIIII")
	end
	trans = ac:GetTransform()
	vc = trans:GetPosition()
	vc.x = vc.x + 1.0
	if vc.x == 20.0 then
		PrintText("I have increased Matias' x-position to 20!")
	end
	trans:SetPosition(vc)
	--ac:SetTransform(trans)
	--trans:PrintPosition()

	myActor = GetActor()

end