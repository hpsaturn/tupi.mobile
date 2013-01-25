package org.kde.necessitas.origo;
 
import android.content.Intent;
import android.util.Log;
import android.net.Uri;

import org.kde.necessitas.origo.QtActivity;

public class QAndroidIntent {
 
    public QAndroidIntent() {
    }
 
    boolean setUrl(String data)
    {
        try {
            Intent sharingIntent = new Intent(Intent.ACTION_SEND);
            sharingIntent.setType("text/plain");
            sharingIntent.putExtra(android.content.Intent.EXTRA_TEXT,  data );
            QtActivity.getQtActivityInstance().startActivity(Intent.createChooser(sharingIntent,"Share using"));

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
