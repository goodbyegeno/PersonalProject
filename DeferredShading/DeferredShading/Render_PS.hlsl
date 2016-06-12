cbuffer MatrixBuffer
{
	float4x4 worldMatrix;
	float4x4 viewProjectionMatrix;
};


struct PSINPUTTYPE
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD0;
	float3 normal	: NORMAL;
	float3 tangent	: TANGENT;
	float3 binormal	: BINORMAL;

};
struct PSOUTPUTTYPE
{
	float4	albedo			: SV_TARGET0
	float4	normal			: SV_TARGET1
	float4	specular		: SV_TARGET2
	float4	position		: SV_TARGET3
};
Texture2D shaderTextures[3];	//0 color 1 normal 2 spec
SamplerState SampleType;

PSOUTPUTTYPE main(PSINPUTTYPE input)
{
	//no alpha mesh;

	PSOUTPUTTYPE output;
	float4 textureColor = shaderTextures[0].Sample(SampleType, input.tex);
	output.albedo = textureColor;

	float4 normalSample = shaderTextures[1].Sample(SampleType, input.tex);
	output.normal = input.normal + normalSample.u * input.tangent + normalSample.v * input.binormal;
	output.normal = normalize(output.normal);

	float4 specularSample = shaderTextures[2].Sample(SampleType, input.tex);
	output.specular = specularSample;

	output.position = 

	return output;
}
