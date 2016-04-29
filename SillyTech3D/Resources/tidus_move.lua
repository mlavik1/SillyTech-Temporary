val = 1;

function Update()
	
	ac = GetActorByName("Tidus")
	if ac == nil then
		PrintText("Actor does not exist")
	end
	trans = ac:GetTransform()
	vc = trans:GetPosition()
	if Input():GetKey("right") == true then 
		vc.x = vc.x + 1.0
	end
	if Input():GetKey("left") == true then 
		vc.x = vc.x - 1.0
	end
	if Input():GetKey("up") == true then 
		vc.y = vc.y + 1.0
	end
	if Input():GetKey("down") == true then 
		vc.y = vc.y - 1.0
	end
	
	if vc.x == 10000.0 then
		PrintText("I have increased Tidus' x-position to 10000!")
	end
	trans:SetPosition(vc)

	rot = vec3(0.0,1.0,1.0)
	trans:Rotate(1.0,rot)
	
	if val == 600 then
		PrintText("JIPPI")
		end
	val = val + 1
	
	--ac2 = GetActorByName("Bergen")
	--trans2 = ac2:GetTransform()
	--vc2 = trans2:GetPosition()
	--vc2.y = vc2.y - 2.0
	--trans2:SetPosition(vc2)
	--vc2 =trans2:GetScale()
	--vc2.y = vc2.y + 0.001
	--trans2:SetScale(vc2)


	myActor = GetActor()

end