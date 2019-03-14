package pl.duch.articles.renderlib;

import android.app.Application;

public class CustomApplication extends Application {

    static {
        System.loadLibrary("softrender");
    }

}
