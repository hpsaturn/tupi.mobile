package org.kde.necessitas.origo;
 
import android.app.Activity;
import android.content.Intent;
import android.util.Log;
 

public class QAndroidIntent extends Activity {
    Intent m_i;
 
    public QAndroidIntent() {
        m_i = new Intent(Intent.ACTION_SEND);
    }
 
    boolean setUrl(String path)
    {
        try {
             Log.d("TUPI",this.getClass().getCanonicalName());


             m_i.setType("text/plain");
             m_i.putExtra(Intent.EXTRA_SUBJECT, "Sharing URL");
             m_i.putExtra(Intent.EXTRA_TEXT, path);
             startActivity(Intent.createChooser(m_i, "Share URL"));

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
