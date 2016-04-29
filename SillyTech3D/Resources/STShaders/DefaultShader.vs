#region begin <INCLUDES>

#include <Common.vsh>

#region end


#region begin <MAIN>

void main()
{
	gl_Position = CalculateMVP();
	v2f_positionW = CalculatePosition();
	v2f_normalW = CalculateNormal();
    v2f_texcoord = CalculateTextureCoordinate();

}

#region end