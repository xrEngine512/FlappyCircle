#pragma once
class GameExport
{
public:
	static void Start();
	static void Stop();
	static void Press();
	static void Play();
	static void Pause();
	static void Release();
	static void Render();
	static void RenderingLoop();
    static bool IsOver();
};

