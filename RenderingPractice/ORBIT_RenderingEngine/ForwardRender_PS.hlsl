Texture2D shaderTexture;
SamplerState sampleType;

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD0;
};


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 main(PixelInputType input) : SV_TARGET
{
	float4 textureColor;


	textureColor = shaderTexture.Sample(sampleType, input.texcoord);

	return textureColor;
}
