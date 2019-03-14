package pl.duch.articles.renderlib;

public class NativeBitmap {

    public static final int PALETTE = 1;
    public static final int ARGB_8888 = 2;

    private final long handler;

    private final int type;
    private final int width;
    private final int height;


    private NativeBitmap(long handler, int type, int width, int height) {
        this.handler = handler;
        this.type = type;
        this.width = width;
        this.height = height;
    }

    public static NativeBitmap createArgb8888(int w, int h) {
        return new NativeBitmap(allocateBitmap(ARGB_8888, w, h), ARGB_8888, w, h);
    }

    public void free() {
        free(this.handler);
    }

    public void dump() {
        dump(this.handler);
    }

    private static native long allocateBitmap(int type, int w, int h);

    private static native void free(long handler);

    private static native void dump(long handler);

    public long getHandler() {
        return handler;
    }

    public int getType() {
        return type;
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }


}

