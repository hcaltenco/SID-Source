/*
  A simple oscilliscope widget test
  
  (c) 2009 David Konsumer <david.konsumer@gmail.com>
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
 */

/*

This shows how to make a single oscilliscope, and feed it values.

*/

import arduinoscope.*;

Oscilloscope scope;

void setup() {
    size(800, 600, P2D);

    int[] dimensions = {width, height};
    int[] position = {0, 0};
    
    scope = new Oscilloscope(this, position, dimensions);
    scope.setLine_color(color(255,0,0));
    scope.setBounds_color(color(0,255,0));    
}

void draw() {
    background(0);
    
    int val = int(random(height*2));
    
    scope.addData(val);
    scope.draw();
    
    scope.drawBounds();  
}

