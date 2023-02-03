using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Net.Mime.MediaTypeNames;

namespace LidarInterface
{
    public partial class Form1 : Form
    {
        bool isMove;

        public Form1()
        {
            isMove = false;
            InitializeComponent();
          
        }




        private void pt1_MouseMove(object sender, MouseEventArgs e)
        {
            // if (e.Button.HasFlag(MouseButtons.Left))
            if (isMove)
            {
                pt1.Left = pt1.Left - (pt1.Width / 2) + e.X;
                pt1.Top = pt1.Top - (pt1.Height / 2) + e.Y;
                drawlinegraph();
            }

        }

        private void pt1_MouseUp(object sender, MouseEventArgs e)
        {
            isMove = false;
        }

        private void pt1_MouseDown(object sender, MouseEventArgs e)
        {
            isMove = true;
        }



        private void pt2_MouseMove(object sender, MouseEventArgs e)
        {
            // if (e.Button.HasFlag(MouseButtons.Left))
            if (isMove)
            {
                pt2.Left = pt2.Left - (pt2.Width / 2) + e.X;
                pt2.Top = pt2.Top - (pt2.Height / 2) + e.Y;
                drawlinegraph();
            }

        }

        private void pt2_MouseUp(object sender, MouseEventArgs e)
        {
            isMove = false;
        }

        private void pt2_MouseDown(object sender, MouseEventArgs e)
        {
            isMove = true;
        }

        private void pt3_MouseMove(object sender, MouseEventArgs e)
        {
            // if (e.Button.HasFlag(MouseButtons.Left))
            if (isMove)
            {
                pt3.Left = pt3.Left - (pt3.Width / 2) + e.X;
                pt3.Top = pt3.Top - (pt3.Height / 2) + e.Y;
                drawlinegraph();
            }

        }

        private void pt3_MouseUp(object sender, MouseEventArgs e)
        {
            isMove = false;
        }

        private void pt3_MouseDown(object sender, MouseEventArgs e)
        {
            isMove = true;
        }

        private void pt4_MouseMove(object sender, MouseEventArgs e)
        {
            // if (e.Button.HasFlag(MouseButtons.Left))
            if (isMove)
            {
                pt4.Left = pt4.Left - (pt4.Width / 2) + e.X;
                pt4.Top = pt4.Top - (pt4.Height / 2) + e.Y;
                drawlinegraph();
            }

        }

        private void pt4_MouseUp(object sender, MouseEventArgs e)
        {
            isMove = false;
        }

        private void pt4_MouseDown(object sender, MouseEventArgs e)
        {
            isMove = true;
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {

            // panel1.Refresh();

        }

        private void drawlinegraph()
        {
            panel1.Refresh();
            Pen pen = new Pen(Color.Red);
            Point[] pts = new Point[5];
            int cpad = (pt1.Width / 2);
            pts[0] = new Point(pt1.Left + cpad, pt1.Top + cpad);
            pts[1] = new Point(pt2.Left + cpad, pt2.Top + cpad);
            pts[2] = new Point(pt3.Left + cpad, pt3.Top + cpad);
            pts[3] = new Point(pt4.Left + cpad, pt4.Top + cpad);
            pts[4] = new Point(pt1.Left + cpad, pt1.Top + cpad);
            //Graphics graphics = new Graphics(); // e.Graphics;

            Graphics g = panel1.CreateGraphics();
            g.DrawLines(pen, pts);
            g.DrawLine(pen, new Point(mpoint.Left, mpoint.Top), new Point(cpoint.Left, cpoint.Top));
        }

        private void drawLineSegment()
        {
            panel1.Refresh();
           

        }


        private bool isInside()
        {

            return false;
        }

        private void Form1_Shown(object sender, EventArgs e)
        {
            drawlinegraph();
            
        }

        private void mpoint_MouseMove(object sender, MouseEventArgs e)
        {

            if (isMove)
            {
                mpoint.Left = mpoint.Left - (mpoint.Width / 2) + e.X;
                mpoint.Top = mpoint.Top - (mpoint.Height / 2) + e.Y;
                drawlinegraph();
                intersection( new PointF(mpoint.Left,mpoint.Top) , new PointF(cpoint.Left, cpoint.Top), new PointF(pt2.Left, pt2.Top), new PointF(pt3.Left, pt3.Top));
            }
            
        }

        private void mpoint_MouseDown(object sender, MouseEventArgs e)
        {
            isMove = true;
        }

        private void mpoint_MouseUp(object sender, MouseEventArgs e)
        {
            isMove = false;
        }

        double intersection(PointF x1,PointF x2, PointF y1, PointF y2)
        {

            float m1 = (x2.Y-x1.Y)/(x2.X-x1.X ) ;
            float b1=0.0f;
            float m2 = (y2.Y - y1.Y) / (y2.X - y1.X); ;
            float b2=0.0f;
            double theta1 = Math.Atan2( (x2.Y - x1.Y), (x2.X - x1.X) );
            double theta2 = Math.Atan2( (y2.Y - y1.Y), (y2.X - y1.X) );
            double theta = (theta1 - theta2) * (180 / Math.PI);


            //if ((m1 - m2) > 0)  // avoid divide by zero 
            //    return 0;
            
            
            //d = (d * 3.14f) / 180.0f;
            textBox1.Text = Convert.ToString( theta  );

            //PointF p = new PointF(0.0f,0.0f);
            //p.X = (b2 - b1) / (m1 - m2);
            //p.Y = p.X * m1 + b1;
            return theta;
        }
    }
}
