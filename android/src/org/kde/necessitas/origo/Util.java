package org.kde.necessitas.origo;

import org.kde.necessitas.example.tupi.R;

import android.app.Dialog;
import android.content.Context;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;


public class Util {
	
	private final static String TAG = Util.class.getSimpleName();
	private static final boolean DEBUG = Config.DEBUG;
	
	public interface OnTaskCompleted {
		void onTaskComplete(String response, int id_task);
		void onTaskError(int errorCode,String errorMsg,int id_task);
	}
	
	public static void getStringForDialog (Context ctx,final OnTaskCompleted listener,final int id){
	    showEditDialog(ctx, 0,0,0, listener, id);
    }
	
	public static void getStringForDialog (Context ctx,final OnTaskCompleted listener,int customlayout, final int id){
        showEditDialog(ctx, 0,0,customlayout,listener, id);
    }
	
	public static void getStringForDialog (Context ctx,int inputType,int textButton,final OnTaskCompleted listener,final int id){
		showEditDialog(ctx, inputType, textButton, 0, listener, id);
	}
	
	private static void showEditDialog (Context ctx,int inputType,int textButton,int customlayout,final OnTaskCompleted listener,final int id){
        
        try {
            final Dialog inputDialog = new Dialog(ctx,R.style.CustomDialogTheme);
            if(customlayout==0)inputDialog.setContentView(R.layout.poi_add_dialog);
            else inputDialog.setContentView(customlayout);
            final EditText edit = (EditText)inputDialog.findViewById(R.id.ed_name);
            if(inputType!=0)edit.setInputType(inputType);
            Button _btn_input = (Button)inputDialog.findViewById(R.id.btn_dialog_accept);
            if(inputType!=0)_btn_input.setText(textButton);
            _btn_input.setOnClickListener(new OnClickListener() {
                
                @Override
                public void onClick(View v) {
                    inputDialog.dismiss();
                    listener.onTaskComplete(edit.getText().toString(), id);
                    
                }
            });
            
            inputDialog.show();
            
        } catch (Exception e) {
            if(DEBUG)Log.d(TAG,"getStringForDialog Exception:");
            e.printStackTrace();
        }
        
    }

}
