using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Emgu.CV;
using Emgu.CV.Structure;
using Emgu.Util;

using System.IO.Ports;

namespace CameraCapture
{
   public partial class CameraCapture : Form
   {
      private Capture _capture;
      private bool _captureInProgress;
      private int min;
      private int max;
      private int distance;
      private int _bubbleLine = 119;
      private int bubbleLine
      {
          get
          {
              return _bubbleLine;
          }
          set
          {
              _bubbleLine = trackBarBubbleLine.Maximum - value;
          }
      }
      Bitmap processedBitmap = new Bitmap(160, 120);

      SerialPort port;

      public CameraCapture()
      {
         InitializeComponent();
         min = trackBarMin.Value;
         max = trackBarMax.Value;
      }

      /// <summary>
      /// Processes every frame, and determins the distanse from the tube to an object
      /// </summary>
      /// <param name="sender"></param>
      /// <param name="arg"></param>
      private void ProcessFrame(object sender, EventArgs arg)
      {
         Image<Bgr, Byte> frame = _capture.QueryFrame();
         Image<Gray, Byte> grayFrame = frame.Convert<Gray, Byte>();
         Image<Gray, Byte> smallGrayFrame = grayFrame.PyrDown();

         Bitmap grayBitmap = smallGrayFrame.ToBitmap();
         Color color;
         int closestPixelH = 0;
         int closestPixelW = 0;
          for (int w = 0; w < grayBitmap.Width; w++)
          {
              for (int h = 0; h < grayBitmap.Height; h++)
              {
                  if (h < bubbleLine)
                  {
                      color = grayBitmap.GetPixel(w, h);
                      if (color.R > min && color.R < max)
                      {
                          processedBitmap.SetPixel(w, h, Color.White);
                      }
                      else
                      {
                          processedBitmap.SetPixel(w, h, Color.Black);
                          //Determine which pixel is closest to the bubble bottle
                          if (closestPixelH < h)
                          {
                              closestPixelH = h;
                              closestPixelW = w;
                          }
                      }
                  }
                  else
                  {
                      processedBitmap.SetPixel(w, h, Color.Gray);
                  }
              }
          }
          //Draw a red square where the closest tracked pixel is
          for (int i = 2; i > -2; i--)
          {
              for (int j = 0; j > -5; j--)
              {
                  try
                  {
                      processedBitmap.SetPixel(closestPixelW + i, closestPixelH + j, Color.Red);
                  }
                  catch { }
              }
          }
          DrawBubbleLine();
          //Send to Arduino if the distance changes
          if (distance != bubbleLine - closestPixelH - 1)
          {
              distance = bubbleLine - closestPixelH - 1;
              if(port != null)
                  if (port.IsOpen)
                  {
                      SendToArduino(distance);
                  }
          }
          labelDistance.Text = distance.ToString();
          pictureBox1.Image = processedBitmap;
          captureImageBox.Image = frame;
      }

      private void captureButtonClick(object sender, EventArgs e)
      {
         #region if capture is not created, create it now
         if (_capture == null)
         {
            try
            {
               _capture = new Capture();
            }
            catch (NullReferenceException excpt)
            {
               MessageBox.Show(excpt.Message);
            }
         }
         #endregion

         if (_capture != null)
         {
            if (_captureInProgress)
            {  //stop the capture
               captureButton.Text = "Start Capture";
               Application.Idle -= ProcessFrame;
            }
            else
            {
               //start the capture
               captureButton.Text = "Stop";
               Application.Idle += ProcessFrame;
            }
            
            _captureInProgress = !_captureInProgress;
         }
      }

      private void ReleaseData()
      {
         if (_capture != null)
            _capture.Dispose();
      }

      private void FlipHorizontalButtonClick(object sender, EventArgs e)
      {
         if (_capture != null) _capture.FlipHorizontal = !_capture.FlipHorizontal;
      }

      private void FlipVerticalButtonClick(object sender, EventArgs e)
      {
         if (_capture != null) _capture.FlipVertical = !_capture.FlipVertical;
      }

      private void trackBarMin_ValueChanged(object sender, EventArgs e)
      {
          textBoxMin.Text = trackBarMin.Value.ToString();
      }

      private void trackBarMax_ValueChanged(object sender, EventArgs e)
      {
          textBoxMax.Text = trackBarMax.Value.ToString();
      }

      private void textBoxMin_TextChanged(object sender, EventArgs e)
      {
          try
          {
              trackBarMin.Value = Convert.ToInt32(textBoxMin.Text);
              min = Convert.ToInt32(textBoxMin.Text);
          }
          catch{}
      }

      private void textBoxMax_TextChanged(object sender, EventArgs e)
      {
          try
          {
              trackBarMax.Value = Convert.ToInt32(textBoxMax.Text);
              max = Convert.ToInt32(textBoxMax.Text);
          }
          catch{}
      }

      private void trackBarBubbleLine_ValueChanged(object sender, EventArgs e)
      {
          textBoxBubbleLine.Text = trackBarBubbleLine.Value.ToString();
          bubbleLine = trackBarBubbleLine.Value;
          DrawBubbleLine();
      }

      private void textBoxBubbleLine_TextChanged(object sender, EventArgs e)
      {
          try
          {
              trackBarBubbleLine.Value = Convert.ToInt32(textBoxBubbleLine.Text);
          }
          catch{}
      }

      private void DrawBubbleLine()
      {
          for (int w = 0; w < processedBitmap.Width; w++)
          {
              processedBitmap.SetPixel(w, bubbleLine, Color.Blue);
          }
      }

      private void SendToArduino(int valueToSend)
      {
          port.Write(valueToSend.ToString() + "\n");
          labelSend.Text = valueToSend.ToString();
      }

      private void buttonConnect_Click(object sender, EventArgs e)
      {
          if (port != null)
              if (port.IsOpen)
              {
                  port.Close();
              }
          port = new SerialPort(textBoxPort.Text, Convert.ToInt32(textBoxBaudRate.Text));
          try
          {
              port.Open();
              labelStatus.Text = "Connected";
              SendToArduino(distance);
          }
          catch (Exception ex)
          {
              MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
          }
      }
   }
}
