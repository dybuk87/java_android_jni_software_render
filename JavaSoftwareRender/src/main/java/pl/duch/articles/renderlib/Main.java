package pl.duch.articles.renderlib;

public class Main {

    static {
        System.loadLibrary("softrender");
    }


    public static void main(String[] args) {
        NativeBitmap nativeBitmap = NativeBitmap.createArgb8888(5, 3);
        System.out.println(nativeBitmap.getHandler());

        nativeBitmap.dump();
        nativeBitmap.free();;
    }


}
