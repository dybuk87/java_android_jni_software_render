#include <jni.h>
#include <iostream>
#include <cstring>
/* 
 * File:   pl_duch_articles_renderlib_NativeBitmap.h
 * Author: duch
 *
 * Created on 28 lutego 2019, 12:56
 */

#ifndef _Included_pl_duch_articles_renderlib_NativeBitmap
#define _Included_pl_duch_articles_renderlib_NativeBitmap
#ifdef __cplusplus
extern "C" {
#endif
#undef pl_duch_articles_renderlib_NativeBitmap_PALETTE
#define pl_duch_articles_renderlib_NativeBitmap_PALETTE 1L
#undef pl_duch_articles_renderlib_NativeBitmap_ARGB_8888
#define pl_duch_articles_renderlib_NativeBitmap_ARGB_8888 2L
    
#define uint32 unsigned int
#define byte unsigned char    
    
    using namespace std;
    
class NativeBitmap {
public:
    NativeBitmap(int bpp, int width, int height);
    ~NativeBitmap();
    
     void setColor(int x, int y, uint32 col);

    uint32 getColor(int x, int y);

    void dump(int withPal);

private:
    int bpp;
    int resX;
    int resY;

    int palSize;

    unique_ptr<byte[]> data;
    unique_ptr<byte[]> palette;
};    
    
/*
 * Class:     pl_duch_articles_renderlib_NativeBitmap
 * Method:    allocateBitmap
 * Signature: (III)J
 */
JNIEXPORT jlong JNICALL Java_pl_duch_articles_renderlib_NativeBitmap_allocateBitmap
  (JNIEnv *, jclass, jint, jint, jint);

/*
 * Class:     pl_duch_articles_renderlib_NativeBitmap
 * Method:    dump
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_pl_duch_articles_renderlib_NativeBitmap_dump
  (JNIEnv *, jclass, jlong);

/*
 * Class:     pl_duch_articles_renderlib_NativeBitmap
 * Method:    free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_pl_duch_articles_renderlib_NativeBitmap_free
  (JNIEnv *, jclass, jlong);

#ifdef __cplusplus
}
#endif
#endif


