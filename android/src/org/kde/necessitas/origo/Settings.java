package org.kde.necessitas.origo;

import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;


public class Settings {
	
	public static boolean isFirstTime(){
		SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(QtActivity.getQtActivityInstance());
		return preferences.getBoolean(SettingsFields.firstTime, false);
	}
	
	public static void  setFirstTime(){
		SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(QtActivity.getQtActivityInstance());
		SharedPreferences.Editor editor = preferences.edit();
		editor.putBoolean(SettingsFields.firstTime, true);
		editor.commit();
	}
	
	public static String getLastSave(){
		SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(QtActivity.getQtActivityInstance());
		return preferences.getString(SettingsFields.lastSave, "");
	}
	
	public static void  setLastSave(String frameString){
		SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(QtActivity.getQtActivityInstance());
		SharedPreferences.Editor editor = preferences.edit();
		editor.putString(SettingsFields.lastSave, frameString);
		editor.commit();
	}

}
