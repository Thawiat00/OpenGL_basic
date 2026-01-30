// เหมือนเราประกาศ :root ใน CSS
// 1. Header Guard: ป้องกันการโหลดไฟล์ซ้ำซ้อน
#ifndef MY_GLOBAL_SKYBOX
#define MY_GLOBAL_SKYBOX



// ตัวแปรที่เราจะ "ละเลง"
// 2. รับค่าจาก C# (Unity Global Variables)
// ใน OpenGL ค่าเหล่านี้จะถูกมองเป็น Uniform
// ===== Global uniforms (มาจาก C# Shader.SetGlobalXXX) =====
uniform float4 _GlobalSkyColor;
uniform float4 _GlobalGroundColor;
uniform float _GlobalAtmosphereThickness;


// ฟังก์ชันแม่แบบสำหรับคำนวณท้องฟ้า
// 3. ฟังก์ชันคำนวณท้องฟ้า (ตัวอย่างแบบ Gradient ง่ายๆ)
// แก้บรรทัดนี้ให้มี float3 sunDir เพิ่มเข้ามา
// ===== Procedural Sky Function =====
float3 CalculateProceduralSky(float3 viewDir, float3 sunDir)
{
    viewDir = normalize(viewDir);
    sunDir = normalize(sunDir);

    // Gradient sky
    float t = saturate(viewDir.y * 0.5 + 0.5);
    float3 sky = lerp(_GlobalGroundColor.rgb, _GlobalSkyColor.rgb, t);

    // Sun disk
    float sunDot = saturate(dot(viewDir, sunDir));
    float sunDisk = pow(sunDot, 256.0);
    sky += sunDisk * 2.0;

    return sky * _GlobalAtmosphereThickness;
}


#endif