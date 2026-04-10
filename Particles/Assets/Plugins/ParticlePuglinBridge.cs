using UnityEngine;
using System.Runtime.InteropServices;
using System;

public class ParticlePuglinBridge : MonoBehaviour
{
    // Estructura que debe coincidir con la de C++
    [StructLayout(LayoutKind.Sequential)]
    public struct Particle
    {
        public Vector3 position;
        public Vector3 velocity;
        public float life;
    }

    // Importar funciones de C++
    [DllImport("NativeParticle")]
    private static extern void InitParticles(int count);

    [DllImport("NativeParticle")]
    private static extern void UpdateParticles(float deltaTime, float speed);

    [DllImport("NativeParticle")]
    private static extern IntPtr GetParticles(); // Usamos IntPtr para memoria nativa

    [DllImport("NativeParticle")]
    private static extern int GetParticleCount();

    public int particleCount = 1000;
    public float simulationSpeed = 1.0f;
    public GameObject particlePrefab;

    private Transform[] particleTransforms;

    void Start()
    {
        InitParticles(particleCount);
        particleTransforms = new Transform[particleCount];
        for (int i = 0; i < particleCount; i++)
        {
            GameObject go = Instantiate(particlePrefab);
            // Hacer que parezcan chispas pequeñitas en vez de gotas
            go.transform.localScale = new Vector3(0.1f, 0.1f, 0.1f);
            particleTransforms[i] = go.transform;
        }
    }

    void Update()
    {
        // 1. Actualizar lógica en C++
        UpdateParticles(Time.deltaTime, simulationSpeed);

        // 2. Obtener datos de C++
        IntPtr particlePtr = GetParticles();
        int size = Marshal.SizeOf(typeof(Particle));

        // 3. Aplicar posiciones a Unity
        for (int i = 0; i < particleCount; i++)
        {
            IntPtr currentParticlePtr = new IntPtr(particlePtr.ToInt64() + i * size);
            Particle p = Marshal.PtrToStructure<Particle>(currentParticlePtr);
            particleTransforms[i].position = p.position;
        }
    }
}
