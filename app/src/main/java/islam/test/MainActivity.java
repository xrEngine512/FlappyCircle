package islam.test;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;

public class MainActivity extends Activity implements SurfaceHolder.Callback {
    private Surface surface;
    private Thread thread = null;
    private boolean isRestarting = false;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        SurfaceView surfaceView = (SurfaceView)findViewById(R.id.surface_view);

        surfaceView.getHolder().addCallback(this);
        surfaceView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(thread == null)
                    StartGame();
            }
        });
        surfaceView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (thread != null) {
                    if (event.getAction() == android.view.MotionEvent.ACTION_DOWN) {
                        if(NativeGameWrapper.IsOver()) {
                            RestartGame();
                            isRestarting = true;
                        }
                        else
                            NativeGameWrapper.Press();
                    }
                    else if(event.getAction() == android.view.MotionEvent.ACTION_UP &&
                            !isRestarting){
                        NativeGameWrapper.Release();
                    }
                    else if(isRestarting)
                        isRestarting = false;
                }
                return thread != null;
            }
        });
    }

    private void StartGame()
    {
        class ThreadFunc implements Runnable {
            @Override
            public void run() {
                NativeGameWrapper.SetSurface(surface);
                NativeGameWrapper.Start();
                Log.println(0,"thread", "ended");
            }
        }
        if (thread == null) {
            thread = new Thread(new ThreadFunc());
            thread.start();
        }
    }

    private void RestartGame() {
        if (thread != null) {
            NativeGameWrapper.Stop();
            try {
                thread.join();
            } catch (InterruptedException ex) {

            }

            thread = null;

            StartGame();

        }
    }

    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
       surface = holder.getSurface();
    }

    public void surfaceCreated(SurfaceHolder holder) {
    }

    public void surfaceDestroyed(SurfaceHolder holder) {
        surface = null;
    }
}
