import processing.core.*; 
import processing.xml.*; 

import msafluid.*; 
import processing.opengl.*; 
import javax.media.opengl.*; 
import java.nio.FloatBuffer; 
import com.sun.opengl.util.*; 
import TUIO.*; 

import java.applet.*; 
import java.awt.Dimension; 
import java.awt.Frame; 
import java.awt.event.MouseEvent; 
import java.awt.event.KeyEvent; 
import java.awt.event.FocusEvent; 
import java.awt.Image; 
import java.io.*; 
import java.net.*; 
import java.text.*; 
import java.util.*; 
import java.util.zip.*; 
import java.util.regex.*; 

public class MSAFluidTuioDemo extends PApplet {

/***********************************************************************
 * 
 * Demo of the MSAFluid library (www.memo.tv/msafluid_for_processing) controlled by TUIO
 * Move mouse to add dye and forces to the fluid.
 * Alternatively use a TUIO tracker/server to control remotely (www.tuio.org)
 * 
 * Click mouse to turn off fluid rendering seeing only particles and their paths.
 * Demonstrates feeding input into the fluid and reading data back (to update the particles).
 * Also demonstrates using Vertex Arrays for particle rendering.
 * 
/***********************************************************************
 
 Copyright (c) 2008, 2009, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of MSA Visuals nor the names of its contributors 
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE. 
 *
 * ***********************************************************************/ 






final float FLUID_WIDTH = 120;

float invWidth, invHeight;    // inverse of screen dimensions
float aspectRatio, aspectRatio2;

MSAFluidSolver2D fluidSolver;

ParticleSystem particleSystem;

PImage imgFluid;

boolean drawFluid = true;

public void setup() {
    size(1280, 768, OPENGL);    // use OPENGL rendering for bilinear filtering on texture
//    size(screen.width * 49/50, screen.height * 49/50, OPENGL);
    hint( ENABLE_OPENGL_4X_SMOOTH );    // Turn on 4X antialiasing

    invWidth = 1.0f/width;
    invHeight = 1.0f/height;
    aspectRatio = width * invHeight;
    aspectRatio2 = aspectRatio * aspectRatio;

    // create fluid and set options
    fluidSolver = new MSAFluidSolver2D((int)(FLUID_WIDTH), (int)(FLUID_WIDTH * height/width));
    fluidSolver.enableRGB(true).setFadeSpeed(0.003f).setDeltaT(0.5f).setVisc(0.0001f);

    // create image to hold fluid picture
    imgFluid = createImage(fluidSolver.getWidth(), fluidSolver.getHeight(), RGB);

    // create particle system
    particleSystem = new ParticleSystem();

    // init TUIO
    initTUIO();
}


public void mouseMoved() {
    float mouseNormX = mouseX * invWidth;
    float mouseNormY = mouseY * invHeight;
    float mouseVelX = (mouseX - pmouseX) * invWidth;
    float mouseVelY = (mouseY - pmouseY) * invHeight;

    addForce(mouseNormX, mouseNormY, mouseVelX, mouseVelY);
}

public void draw() {
    updateTUIO();
    fluidSolver.update();

    if(drawFluid) {
        for(int i=0; i<fluidSolver.getNumCells(); i++) {
            int d = 2;
            imgFluid.pixels[i] = color(fluidSolver.r[i] * d, fluidSolver.g[i] * d, fluidSolver.b[i] * d);
        }  
        imgFluid.updatePixels();//  fastblur(imgFluid, 2);
        image(imgFluid, 0, 0, width, height);
    } 

    particleSystem.updateAndDraw();

}

public void mousePressed() {
    //drawFluid ^= true;
}

public void keyPressed() {
    switch(key) {
    case 'r': 
        renderUsingVA ^= true; 
        println("renderUsingVA: " + renderUsingVA);
        break;
    }
}



// add force and dye to fluid, and create particles
public void addForce(float x, float y, float dx, float dy) {
    float speed = dx * dx  + dy * dy * aspectRatio2;    // balance the x and y components of speed with the screen aspect ratio

    if(speed > 0) {
        if(x<0) x = 0; 
        else if(x>1) x = 1;
        if(y<0) y = 0; 
        else if(y>1) y = 1;

        float colorMult = 5;
        float velocityMult = 30.0f;

        int index = fluidSolver.getIndexForNormalizedPosition(x, y);

        int drawColor;

        colorMode(HSB, 360, 1, 1);
        float hue = ((x + y) * 180 + frameCount) % 360;
        drawColor = color(hue, 1, 1);
        colorMode(RGB, 1);  

        fluidSolver.rOld[index]  += red(drawColor) * colorMult;
        fluidSolver.gOld[index]  += green(drawColor) * colorMult;
        fluidSolver.bOld[index]  += blue(drawColor) * colorMult;

        particleSystem.addParticles(x * width, y * height, 10);
        fluidSolver.uOld[index] += dx * velocityMult;
        fluidSolver.vOld[index] += dy * velocityMult;
    }
}

/***********************************************************************
 
 Copyright (c) 2008, 2009, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of MSA Visuals nor the names of its contributors 
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE. 
 *
 * ***********************************************************************/ 

class Particle {
    final static float MOMENTUM = 0.5f;
    final static float FLUID_FORCE = 0.6f;

    float x, y;
    float vx, vy;
    float radius;       // particle's size
    float alpha;
    float mass;

    public void init(float x, float y) {
        this.x = x;
        this.y = y;
        vx = 0;
        vy = 0;
        radius = 5;
        alpha  = random(0.3f, 1);
        mass = random(0.1f, 1);
    }


    public void update() {
        // only update if particle is visible
        if(alpha == 0) return;

        // read fluid info and add to velocity
        int fluidIndex = fluidSolver.getIndexForNormalizedPosition(x * invWidth, y * invHeight);
        vx = fluidSolver.u[fluidIndex] * width * mass * FLUID_FORCE + vx * MOMENTUM;
        vy = fluidSolver.v[fluidIndex] * height * mass * FLUID_FORCE + vy * MOMENTUM;

        // update position
        x += vx;
        y += vy;

        // bounce of edges
        if(x<0) {
            x = 0;
            vx *= -1;
        }
        else if(x > width) {
            x = width;
            vx *= -1;
        }

        if(y<0) {
            y = 0;
            vy *= -1;
        }
        else if(y > height) {
            y = height;
            vy *= -1;
        }

        // hackish way to make particles glitter when the slow down a lot
        if(vx * vx + vy * vy < 1) {
            vx = random(-1, 1);
            vy = random(-1, 1);
        }

        // fade out a bit (and kill if alpha == 0);
        alpha *= 0.999f;
        if(alpha < 0.01f) alpha = 0;

    }


    public void updateVertexArrays(int i, FloatBuffer posBuffer, FloatBuffer colBuffer) {
        int vi = i * 4;
        posBuffer.put(vi++, x - vx);
        posBuffer.put(vi++, y - vy);
        posBuffer.put(vi++, x);
        posBuffer.put(vi++, y);

        int ci = i * 6;
        colBuffer.put(ci++, alpha);
        colBuffer.put(ci++, alpha);
        colBuffer.put(ci++, alpha);
        colBuffer.put(ci++, alpha);
        colBuffer.put(ci++, alpha);
        colBuffer.put(ci++, alpha);
    }


    public void drawOldSchool(GL gl) {
        gl.glColor3f(alpha, alpha, alpha);
        gl.glVertex2f(x-vx, y-vy);
        gl.glVertex2f(x, y);
    }

}








/***********************************************************************
 
 Copyright (c) 2008, 2009, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of MSA Visuals nor the names of its contributors 
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE. 
 *
 * ***********************************************************************/ 




boolean renderUsingVA = true;

public void fadeToColor(GL gl, float r, float g, float b, float speed) {
    gl.glBlendFunc(GL.GL_SRC_ALPHA, GL.GL_ONE_MINUS_SRC_ALPHA);
    gl.glColor4f(r, g, b, speed);
    gl.glBegin(GL.GL_QUADS);
    gl.glVertex2f(0, 0);
    gl.glVertex2f(width, 0);
    gl.glVertex2f(width, height);
    gl.glVertex2f(0, height);
    gl.glEnd();
}


class ParticleSystem {
    FloatBuffer posArray;
    FloatBuffer colArray;

    final static int maxParticles = 5000;
    int curIndex;

    Particle[] particles;

    ParticleSystem() {
        particles = new Particle[maxParticles];
        for(int i=0; i<maxParticles; i++) particles[i] = new Particle();
        curIndex = 0;

        posArray = BufferUtil.newFloatBuffer(maxParticles * 2 * 2);// 2 coordinates per point, 2 points per particle (current and previous)
        colArray = BufferUtil.newFloatBuffer(maxParticles * 3 * 2);
    }


    public void updateAndDraw(){
        PGraphicsOpenGL pgl = (PGraphicsOpenGL) g;         // processings opengl graphics object
        GL gl = pgl.beginGL();                // JOGL's GL object

        gl.glEnable( GL.GL_BLEND );             // enable blending
        if(!drawFluid) fadeToColor(gl, 0, 0, 0, 0.05f);

        gl.glBlendFunc(GL.GL_ONE, GL.GL_ONE);  // additive blending (ignore alpha)
        gl.glEnable(GL.GL_LINE_SMOOTH);        // make points round
        gl.glLineWidth(1);


        if(renderUsingVA) {
            for(int i=0; i<maxParticles; i++) {
                if(particles[i].alpha > 0) {
                    particles[i].update();
                    particles[i].updateVertexArrays(i, posArray, colArray);
                }
            }    
            gl.glEnableClientState(GL.GL_VERTEX_ARRAY);
            gl.glVertexPointer(2, GL.GL_FLOAT, 0, posArray);

            gl.glEnableClientState(GL.GL_COLOR_ARRAY);
            gl.glColorPointer(3, GL.GL_FLOAT, 0, colArray);

            gl.glDrawArrays(GL.GL_LINES, 0, maxParticles * 2);
        } 
        else {
            gl.glBegin(GL.GL_LINES);               // start drawing points
            for(int i=0; i<maxParticles; i++) {
                if(particles[i].alpha > 0) {
                    particles[i].update();
                    particles[i].drawOldSchool(gl);    // use oldschool renderng
                }
            }
            gl.glEnd();
        }

        gl.glDisable(GL.GL_BLEND);
        pgl.endGL();
    }


    public void addParticles(float x, float y, int count ){
        for(int i=0; i<count; i++) addParticle(x + random(-15, 15), y + random(-15, 15));
    }


    public void addParticle(float x, float y) {
        particles[curIndex].init(x, y);
        curIndex++;
        if(curIndex >= maxParticles) curIndex = 0;
    }

}








/***********************************************************************
 
 Copyright (c) 2008, 2009, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of MSA Visuals nor the names of its contributors 
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE. 
 *
 * ***********************************************************************/ 


TuioProcessing tuioClient;

final static float tuioCursorSpeedMult = 0.02f; // the iphone screen is so small, easy to rack up huge velocities! need to scale down 
final static float tuioStationaryForce = 0.001f; // force exerted when cursor is stationary
final static float tuioDoubleTapDistanceThreshold2 = 0.01f; // distance squared (in tuio units) of last two taps in order to count as doubletap
final static float tuioDoubleTapTimeThreshold = 0.2f; // seconds between last two taps in order to count as doubletap

TuioPoint tuioLastTap;        // stores last tap information (to detect double tap)
boolean tuioDoubleTap = false;

public void initTUIO() {
    tuioClient  = new TuioProcessing(this);
}


public void updateTUIO() {
    Vector tuioCursorList = tuioClient.getTuioCursors();
    for (int i=0;i<tuioCursorList.size();i++) {
        TuioCursor tcur = (TuioCursor)tuioCursorList.elementAt(i);
        float vx = tcur.getXSpeed() * tuioCursorSpeedMult;
        float vy = tcur.getYSpeed() * tuioCursorSpeedMult;
        if(vx == 0 && vy == 0) {
            vx = random(-tuioStationaryForce, tuioStationaryForce);
            vy = random(-tuioStationaryForce, tuioStationaryForce);
        }
        addForce(tcur.getX(), tcur.getY(), vx, vy);
    }


    if(tuioDoubleTap) {
//        drawFluid ^= true;
        tuioDoubleTap = false;
    }
}

public void addTuioObject(TuioObject tobj) {
}

public void updateTuioObject(TuioObject tobj) {
}

public void removeTuioObject(TuioObject tobj) {
}



public void addTuioCursor(TuioCursor tcur) {
    // check for double tap
    if(tuioLastTap != null) {  // only do this if we have a previous tap
    float timeMult = 0.000001f;   // getTotalMilliseconds seems to be returning microseconds instead of milliseconds in current TUIO client library :/
        float nowTime = tcur.getTuioTime().getTotalMilliseconds() * timeMult;
        float lastTime = tuioLastTap.getTuioTime().getTotalMilliseconds() * timeMult;
//        println(nowTime + " - " + lastTime);
        if(nowTime - lastTime < tuioDoubleTapTimeThreshold) {    // check time different between current and previous tap
            float dx = tcur.getX() - tuioLastTap.getX(); // horizontal distance
            float dy = tcur.getY() - tuioLastTap.getY(); // vertical distance
            float d2 = dx * dx + dy * dy; // square of distance between taps
//            println(d2);
            if(d2 < tuioDoubleTapDistanceThreshold2) tuioDoubleTap = true; 
        }
    }

    tuioLastTap = new TuioPoint(tcur); // store info for next tap
}

public void updateTuioCursor(TuioCursor tcur) {
}

public void removeTuioCursor(TuioCursor tcur) {
}

public void refresh(TuioTime bundleTime) {
}










  static public void main(String args[]) {
    PApplet.main(new String[] { "--bgcolor=#F0F0F0", "MSAFluidTuioDemo" });
  }
}
