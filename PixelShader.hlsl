struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    float m_angle;
    float3 m_color;
    bool isRandom;
}

float4 psmain(PS_INPUT input) : SV_Target
{
    return !isRandom ? float4(m_color, 1.0f) : float4(lerp(input.color, input.color1, (sin(m_angle) + 1.0f) / 2.0f), 1.0f);
}
