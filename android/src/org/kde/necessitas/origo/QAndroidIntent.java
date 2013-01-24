package org.kde.necessitas.origo;
 
import android.app.Activity;
import android.content.Intent;
import android.util.Log;
 

public class QAndroidIntent {
 
    public QAndroidIntent() {
    }
 
    boolean setUrl(String url)
    {
        try {
             Log.d("TUPI class: ", this.getClass().getCanonicalName());
             Log.d("TUPI url:   ", url);

        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
        Log.i("Qt", "Intent returned");
        return true;
    }

    boolean release()
    {
        try {
            //m_i.release();
        }
        catch (Exception e) {
            e.printStackTrace();
            return false;
        }
        return true;
    }

 }
