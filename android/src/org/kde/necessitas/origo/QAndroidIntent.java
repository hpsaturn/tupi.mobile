/***************************************************************************
 *   Project TUPI: Open 2D Magic                                           *
 *   Component: tupi.mobile                                                *
 *   Project Contact: info@maefloresta.com                                 *
 *   Project Website: http://www.maefloresta.com                           *
 *                                                                         *
 *   Developers:                                                           *
 *   2012:                                                                 *
 *    Gustavo Gonzalez / @xtingray                                         *
 *    Andres Calderon / @andresfcalderon                                   *
 *    Antonio Vanegas / @hpsaturn                                          *
 *                                                                         *
 *   Copyright (C) 2012 Mae Floresta - http://www.maefloresta.com          *
 *   License:                                                              *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

package org.kde.necessitas.origo;

import org.kde.necessitas.origo.Util.OnTaskCompleted;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Environment;
import android.preference.PreferenceManager;
import android.util.Log;

public class QAndroidIntent implements OnTaskCompleted {

	private final String TAG = QAndroidIntent.class.getSimpleName();
	private static final boolean DEBUG = Config.DEBUG;
	private static final int TASK_DIALOG = 0;

	public QAndroidIntent() {
	}

	boolean setUrl(String data) {
		try {
			if (DEBUG)Log.d(TAG, "SHARE INTENT");
			Intent sharingIntent = new Intent(Intent.ACTION_SEND);
			sharingIntent.setType("text/plain");
			sharingIntent.putExtra(android.content.Intent.EXTRA_TEXT, data);
			QtActivity.getQtActivityInstance().startActivity(Intent.createChooser(sharingIntent, "Share using"));
			// if(DEBUG)Log.d(TAG,"MEDIA STORAGE: "+getMediaStorage());

		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
		Log.i(TAG, "setUrlStart");
		return true;
	}

	String getMediaStorage() {
		
		if (DEBUG)Log.d(TAG, "MEDIA STORAGE: ");

		try {
			QtActivity.getQtActivityInstance().startActivity(new Intent(QtActivity.getQtActivityInstance(),DetailsActivity.class));
			
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		//dialog.show();

		// Util.getStringForDialog(QtActivity.getQtActivityInstance(), this,
		// TASK_DIALOG);

		if (DEBUG)Log.d(TAG, "MEDIA STORAGE: ");
		String uri = Environment.getExternalStorageDirectory().toString();
		if (DEBUG)Log.d(TAG, "" + uri);
		return uri;
	}
	
	public boolean isFirstTime(){
		SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(QtActivity.getQtActivityInstance());
		return preferences.getBoolean(SettingsFields.firstTime, false);
	}
	
	public void  setFirstTime(){
		SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(QtActivity.getQtActivityInstance());
		SharedPreferences.Editor editor = preferences.edit();
		editor.putBoolean(SettingsFields.firstTime, true);
		editor.commit();
	}
	
	public String getLastSave(){
		SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(QtActivity.getQtActivityInstance());
		return preferences.getString(SettingsFields.lastSave, "");
	}
	
	public boolean  setLastSave(String frameString){
		SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(QtActivity.getQtActivityInstance());
		SharedPreferences.Editor editor = preferences.edit();
		editor.putString(SettingsFields.lastSave, frameString);
		editor.commit();
		return true;
	}

	boolean release() {
		try {
			// m_i.release();
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
		return true;
	}

	@Override
	public void onTaskComplete(String response, int id_task) {
		// TODO Auto-generated method stub

	}

	@Override
	public void onTaskError(int errorCode, String errorMsg, int id_task) {
		// TODO Auto-generated method stub

	}

}
