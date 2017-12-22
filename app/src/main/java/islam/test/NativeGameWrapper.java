package islam.test;

import android.view.Surface;

/**
 * Created by bozie on 12.02.2016.
 */
public class NativeGameWrapper {
    static {
        System.loadLibrary("GameLib");
    }

    public static native void SetSurface(Surface surface);
    public static native void Start();
    public static native void Stop();
    public static native void Press();
    public static native void Play();
    public static native void Pause();
    public static native void Release();
    public static native boolean IsOver();
}
