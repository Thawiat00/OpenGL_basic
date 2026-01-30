// เหมือนเราประกาศ :root ใน CSS
// 1. Header Guard: ป้องกันการโหลดไฟล์ซ้ำซ้อน
#ifndef MY_GLOBAL_SKYBOX
#define MY_GLOBAL_SKYBOX


// ตัวแปรที่เราจะ "ละเลง"
// 2. รับค่าจาก C# (Unity Global Variables)
// ใน OpenGL ค่าเหล่านี้จะถูกมองเป็น Uniform
uniform float4 _GlobalSkyColor;
uniform float4 _GlobalGroundColor;
uniform float _GlobalAtmosphereThickness;


// ฟังก์ชันแม่แบบสำหรับคำนวณท้องฟ้า
// 3. ฟังก์ชันคำนวณท้องฟ้า (ตัวอย่างแบบ Gradient ง่ายๆ)
float3 CalculateProdeduralSky(float3 viewDir)
{
    // viewDir.y จะมีค่าระหว่าง -1 (ล่างสุด) ถึง 1 (บนสุด)
    // เราปรับให้เป็น 0 ถึง 1 เพื่อทำ Gradient
    float t = viewDir.y * 0.5 + 0.5;
    
    // ผสมสีระหว่างดินกับฟ้า
    float3 finalColor = lerp(_GlobalGroundColor.rgb, _GlobalSkyColor.rgb, t);
    
    return finalColor * _GlobalAtmosphereThickness;
}


#endif