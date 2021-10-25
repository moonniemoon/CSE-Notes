public class Color implements Comparable {

        final static int BYTE_MASK = 255;
        private long red;
        private long green;
        private long blue;
        private long color;
        
        // rrggbb 0000rr
        // rrggbb 00rrgg 0000gg
        // rrggbb 0000bb
        
        public void rgb2color() {
            red = color >>> 16;
            green = (color >>> 8) & BYTE_MASK;
            blue = color & BYTE_MASK;
        }
        
        private void color2rgb() {
            color = (red<<16) | (green<<8) | (blue);
        }
        public Color() {}
        
        public Color(long col) {
            color = col;
            rgb2color();
        }
        
        public long getRed() {
            return red;
        }
        public long getGreen() {
            return green;
        }
        public long getBlue() {
            return blue;
        }
        public long getColor() {
            return color;
        }
        
        public void setRed(long r) {
            red = r;
            color2rgb();
        }
        public void setGreen(long g) {
            green = g;
            color2rgb();
        }
        public void setBlue(long b) {
            blue = b;
            color2rgb();
        }
        public String toString() {
            return "Red:" + red + " Green:" + green + " Blue:" + blue;
        }
        public boolean equals(Object o) {
            return color == ((Color)o).color;
        }
        @Override
        public int compareTo(Object o) {
            //		if(this.color < ((Color)c).color) return -1;
            //		if(this.color > ((Color)c).color) return 1;
            //		return 0;
            return ((int)this.color - (int)((Color)o).color);
        }
}
