cbuffer MatrixBuffer
{
	float4x4 worldMatrix;
	float4x4 viewProjectionMatrix;
};

struct VSINPUTTYPE
{
	float4 position : POSITION;
	float2 texCoord : TEXCOORD0;
	float3 normal	: NORMAL;
	float3 tangent	: TANGENT;
	float3 binormal	: BINORMAL;
};
struct PSINPUTTYPE
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD0;
	float3 normal	: NORMAL;
	float3 tangent	: TANGENT;
	float3 binormal	: BINORMAL;

};

PSINPUTTYPE main( VSINPUTTYPE input)
{
	PSINPUTTYPE output;

	input.position.w = 1;

	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewProjectionMatrix);
	
	output.texCoord = input.texCoord;
	output.normal = mul(input.normal, worldMatrix);
	output.normal = normalize(output.normal);

	output.tangent = mul(input.tangent, worldMatrix);
	output.tangent = normalize(output.tangent);

	output.binormal = mul(input.binormal, worldMatrix);
	output.binormal = normalize(output.binormal);

	return output;
}