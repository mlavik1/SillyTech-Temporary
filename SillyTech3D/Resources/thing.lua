

function Update()
	
	ac = GetActorByName("Thing")
	if ac == nil then
		PrintText("Actor does not exist")
	end
	trans = ac:GetTransform()
	vc = trans:GetPosition()
	if Input():GetKey("right") == true then 
		vc= vc + trans:Right()
	end
	if Input():GetKey("left") == true then 
		vc= vc - trans:Right()
	end
	if Input():GetKey("up") == true then 
		vc= vc + trans:Forward()
	end
	if Input():GetKey("down") == true then 
		vc= vc - trans:Forward()
	end
	
	trans:SetPosition(vc)

	
	if Input():GetKey("d") == true then 
		trans:Rotate(10.0,trans:Forward()*-1.0)
	end
	if Input():GetKey("a") == true then 
		trans:Rotate(10.0,trans:Forward())
	end
	if Input():GetKey("w") == true then 
		trans:Rotate(10.0,trans:Right())
	end
	if Input():GetKey("s") == true then 
		trans:Rotate(10.0,trans:Right()*-1.0)
	end


end