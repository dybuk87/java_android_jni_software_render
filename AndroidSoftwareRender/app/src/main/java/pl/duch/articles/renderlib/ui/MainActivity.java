package pl.duch.articles.renderlib.ui;

import android.app.Activity;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.util.Log;

import pl.duch.articles.renderlib.NativeBitmap;

public class MainActivity extends Activity {


    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        NativeBitmap nativeBitmap = NativeBitmap.createArgb8888(5, 3);
        Log.i(MainActivity.class.getName(), "HANDLER: " + nativeBitmap.getHandler());

        nativeBitmap.dump();
        nativeBitmap.free();;

    }
}
