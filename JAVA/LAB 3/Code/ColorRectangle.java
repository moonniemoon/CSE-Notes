public class ColorRectangle extends Color implements Comparable{
        private int iX1=0;
        private int iY1=0;
        private int iX2=0;
        private int iY2=0;
        
        public ColorRectangle() {
            super();
        }
        public ColorRectangle(int x1, int y1, int x2, int y2, long c) {
            super(c);
            iX1 = x1<x2?x1:x2;
            iY1 = y1<y2?y1:y2;
            iX2 = x1<x2?x2:x1;
            iY2 = y1<y2?y2:y1;
        }
        
        public int getix1() {
            return iX1;
        }
        public int getiy1() {
            return iY1;
        }
        public int getix2() {
            return iX2;
        }
        public int getiy2() {
            return iY2;
        }
        public void setix1(int x1) {
            iX1 = x1;
        }
        public void setiy1(int y1) {
            iY1 = y1;
        }
        public void setix2(int x2) {
            iX2 = x2;
        }
        public void setiy2(int y2) {
            iY2 = y2;
        }
        
        public int calcArea() {
            return Math.abs(iX1-iX2)*Math.abs(iY1-iY2);
        }
        public int calcPerimeter() {
            return (Math.abs(iX2-iX1)+Math.abs(iY2-iY1))*2;
        }
        
        
        public int compareTo(Object Rec) {
            if (this.calcArea() < ((ColorRectangle)Rec).calcArea()){
                return -1;
            }
            else if (this.calcArea() == ((ColorRectangle)Rec).calcArea()) {
                return 0;
            }
            else {
                return 1;
            }
        }
        
        public boolean equals(ColorRectangle Rec) {
            //return (this.calcArea() == Rec.calcArea());
            return ((this.compareTo(Rec)==0)?true:false)&&(super.equals(Rec));
        }
        
        public String toString() {
            String temp = ("("+iX1+","+iY1+")"+" ("+iX2+","+iY2+")"+" Color: "+super.toString());
            return temp;
        }
        
        public void translateX(int xs) {
            setix1(iX1+xs);
            setix2(iX2+xs);
        }
        public void translateY(int ys) {
            setiy1(iY1+ys);
            setiy2(iY2+ys);
        }
        public void translateXY(int xs, int ys) {
            translateX(xs);
            translateY(ys);
        }
        
        public boolean isInside(int ptX, int ptY) {
            if (ptX >=iX1 && ptX<=iX2 && ptY >=iY1 && ptY <=iY2) {
                return true;
            }
            else return false;
        }
        
        public ColorRectangle unionRect(ColorRectangle rec) {
            int tempx1,tempx2,tempy1,tempy2;
            if (this.getix1()<=rec.getix1()) {
                tempx1 = this.getix1();
            }
            else tempx1 = rec.getix1();
        
            if (this.getix2()>=rec.getix2()) {
                tempx2 = this.getix2();
            }
            else tempx2 = rec.getix2();
        
            if (this.getiy1()<=rec.getiy1()) {
                tempy1 = this.getiy1();
            }
            else tempy1 = rec.getiy1();
        
            if (this.getiy2()>=rec.getiy2()) {
                tempy2 = this.getiy2();
            }
            else tempy2 = rec.getiy2();
        
            ColorRectangle result = new ColorRectangle(tempx1,tempy1,tempx2,tempy2,
                    (new Color(super.getColor() | rec.getColor())).getColor());
            return result;
        }
        
        public ColorRectangle intersectionRect(ColorRectangle rec) {
            int tempx1,tempx2,tempy1,tempy2;
            if (rec.isInside(this.getix1(), this.getiy1())) {
                tempx1 = this.getix1();
                tempy1 = this.getiy1();
            }
            else if (this.isInside(rec.getix1(), rec.getiy1())) {
                tempx1 = rec.getix1();
                tempy1 = rec.getiy1();
            }
            else {
                System.out.println("The rectangles do not intersect. Returning base rectangle.");
                return new ColorRectangle(0,0,0,0,(new Color(super.getColor() & rec.getColor())).getColor());
            }
        
            if (rec.isInside(this.getix2(), this.getiy2())) {
                tempx2 = this.getix2();
                tempy2 = this.getiy2();
            }
            else if (this.isInside(rec.getix2(), rec.getiy2())) {
                tempx2 = rec.getix2();
                tempy2 = rec.getiy2();
            }
            else {
                System.out.println("The rectangles do not intersect. Returning base rectangle.");
                return new ColorRectangle(0,0,0,0,(new Color(super.getColor() & rec.getColor())).getColor());
            }
        
            ColorRectangle result = new ColorRectangle(tempx1,tempy1,tempx2,tempy2,(new Color(super.getColor() & rec.getColor())).getColor());
            return result;
        }

}
