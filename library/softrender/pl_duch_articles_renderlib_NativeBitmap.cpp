/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pl_duch_articles_renderlib_NativeBitmap.cpp
 * Author: duch
 *
 * Created on 28 lutego 2019, 13:03
 */

#include <cstdlib>
#include <jni.h>
#include <iostream>
#include <cstring>
#include "pl_duch_articles_renderlib_NativeBitmap.h"

using namespace std;

NativeBitmap::NativeBitmap(int bpp, int resX, int resY) {
    this->resX = resX;
    this->resY = resY;
    this->bpp = bpp; 

    int totalSize = (resX * resY * bpp) / 8 ;
    this->palSize = bpp > 8 ? 0 : (1 << bpp);

    this->data.reset(new byte[totalSize]);
    
    if (this->palSize > 1) {
        palette.reset(new byte[this->palSize * 4]);    
        
	for(int i=0; i<this->palSize; i++) {
	   palette[i * 4 + 0] = 255 * i / (this->palSize - 1);
	   palette[i * 4 + 1] = 255 * i / (this->palSize - 1);
	   palette[i * 4 + 2] = 255 * i / (this->palSize - 1);
	   palette[i * 4 + 3] = 255;
	}
    }
}

uint32 combine24(int r, int g, int b) {
    return r | (g << 8) | (b << 16);
}

int get24R(uint32 color) {
    return color & 255;
}

int get24G(uint32 color) {
    return (color >> 8) & 255;
}

int get24B(uint32 color) {
    return (color >> 16) & 255;
}

uint32 NativeBitmap::getColor(int x, int y) {
    int index = (x + y * resX);
	
    if (bpp < 8) {
        int byteNo = index * bpp / 8;
        int offsetInByte = (index * bpp) & 7;
        int mask = (1<<bpp) - 1;

        byte val = data[byteNo];
        val >>= offsetInByte;
        val &= mask;	
        
        return val;
    } else {
        int col;
        int byteNo = index * bpp / 8;           
        memcpy(&col, data.get() + byteNo, bpp/8);
        
        return col;
    }
}

void NativeBitmap::setColor(int x, int y, uint32 col) {
	int index = (x + y * resX);
	
	if (bpp < 8) {	
		int byteNo = index * bpp / 8;
		int offsetInByte = (index * bpp) & 7;
		int mask = (1<<bpp) - 1;
		
		col &= mask;
		col <<= offsetInByte;
		data[byteNo] |= col;
	} else {
            int byteNo = index * bpp / 8;
            memcpy(data.get() + byteNo, &col, bpp/8);
	}
}

void NativeBitmap::dump(int withPal) {
	cout<<"Image "<<resX<<"x"<<resY<<" - " << bpp<<endl;
	
        if (this->palSize > 0) {
            cout<<"Palette: "<<endl;
	
            for(int i=0; i<this->palSize; i++) {
                    cout<<"("
                            <<(uint32)palette[i * 4 + 0] <<", "
                            <<(uint32)palette[i * 4 + 1] <<", "
                            <<(uint32)palette[i * 4 + 2] <<", "
                            <<(uint32)palette[i * 4 + 3] << "), ";
            }
            
            cout<<endl;
        }
	cout<<"Image data: "<<endl;

	if (palSize > 0) {
   	    for(int y=0; y<resY; y++) {
		for(int x=0; x<resX; x++) {
			int index = (x + y * resX);
			int byteNo = index * bpp / 8;
			int offsetInByte = (index * bpp) & 7;
			int mask = (1<<bpp) - 1;

			byte val = data[byteNo];
			val >>= offsetInByte;
			val &= mask;
			
			if (withPal) {
				cout<<"("
					<<(uint32)palette[val * 4 + 0] <<", "
					<<(uint32)palette[val * 4 + 1] <<", "
					<<(uint32)palette[val * 4 + 2] <<", "
					<<(uint32)palette[val * 4 + 3] << "), ";
			} else {
				cout<<(uint32)val<<", ";
			}

		}
		cout<<endl;
	    }
	} else {
            for(int y=0; y<resY; y++) {
		for(int x=0; x<resX; x++) {
                    int index = (x + y * resX);
                    int byteNo = index * bpp / 8;
                   
                    cout<<"(";
                    cout<<(int)data[byteNo];
                    for(int i=1; i<bpp/8; i++) {
                        cout<<", "<<(int)data[byteNo + i];
                    }
                    cout<<") ";
                                  
                }
                cout<<endl;
            }
	}

	cout<<endl;
}

NativeBitmap::~NativeBitmap() {
    
}

JNIEXPORT jlong JNICALL Java_pl_duch_articles_renderlib_NativeBitmap_allocateBitmap
  (JNIEnv *env, jclass clazz, jint type, jint width, jint height) {
    
    int bpp = 32;
    if (type == pl_duch_articles_renderlib_NativeBitmap_PALETTE) {
        bpp = 8;
    }
   
    return (jlong)new NativeBitmap(bpp, width, height);
}

JNIEXPORT void JNICALL Java_pl_duch_articles_renderlib_NativeBitmap_free
  (JNIEnv *env, jclass clazz, jlong handler) {
    NativeBitmap *bitmap = (NativeBitmap*)handler;
    
    delete bitmap;
}

JNIEXPORT void JNICALL Java_pl_duch_articles_renderlib_NativeBitmap_dump
  (JNIEnv *env, jclass clazz, jlong handler) {
    NativeBitmap *bitmap = (NativeBitmap*)handler;
    
    bitmap->dump(0);
}

